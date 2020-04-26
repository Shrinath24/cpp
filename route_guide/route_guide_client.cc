#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <sstream>
#include <thread>
#include <fstream>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#ifdef BAZEL_BUILD
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "route_guide.grpc.pb.h"
#endif
using namespace std;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using routeguide::RouteGuide;
using routeguide::Input;
using routeguide::Stats;
using routeguide::List;
static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

const int NUM_CPU_STATES = 10;

enum CPUStates
{
	S_USER = 0,
	S_NICE,
	S_SYSTEM,
	S_IDLE,
	S_IOWAIT,
	S_IRQ,
	S_SOFTIRQ,
	S_STEAL,
	S_GUEST,
	S_GUEST_NICE
};

typedef struct CPUData
{
	std::string cpu;
	size_t times[NUM_CPU_STATES];
} CPUData;

void ReadStatsCPU(std::vector<CPUData> & entries);

size_t GetIdleTime(const CPUData & e);
size_t GetActiveTime(const CPUData & e);

double PrintStats(const std::vector<CPUData> & entries1, const std::vector<CPUData> & entries2);

double getcpustatistics()
{
	std::vector<CPUData> entries1;
	std::vector<CPUData> entries2;

	// snapshot 1
	ReadStatsCPU(entries1);

	// 100ms pause
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// snapshot 2
	ReadStatsCPU(entries2);

	// print output
	return PrintStats(entries1, entries2);
}

void ReadStatsCPU(std::vector<CPUData> & entries)
{
	std::ifstream fileStat("/proc/stat");

	std::string line;

	const std::string STR_CPU("cpu");
	const std::size_t LEN_STR_CPU = STR_CPU.size();
	const std::string STR_TOT("tot");

	while(std::getline(fileStat, line))
	{
		// cpu stats line found
		if(!line.compare(0, LEN_STR_CPU, STR_CPU))
		{
			std::istringstream ss(line);

			// store entry
			entries.emplace_back(CPUData());
			CPUData & entry = entries.back();

			// read cpu label
			ss >> entry.cpu;

			// remove "cpu" from the label when it's a processor number
			if(entry.cpu.size() > LEN_STR_CPU)
				entry.cpu.erase(0, LEN_STR_CPU);
			// replace "cpu" with "tot" when it's total values
			else
				entry.cpu = "";

			// read times
			for(int i = 0; i < NUM_CPU_STATES; ++i)
				ss >> entry.times[i];
		}
	}
}

size_t GetIdleTime(const CPUData & e)
{
	return	e.times[S_IDLE] +
			e.times[S_IOWAIT];
}

size_t GetActiveTime(const CPUData & e)
{
	return	e.times[S_USER] +
			e.times[S_NICE] +
			e.times[S_SYSTEM] +
			e.times[S_IRQ] +
			e.times[S_SOFTIRQ] +
			e.times[S_STEAL] +
			e.times[S_GUEST] +
			e.times[S_GUEST_NICE];
}

double PrintStats(const std::vector<CPUData> & entries1, const std::vector<CPUData> & entries2)
{
	const size_t NUM_ENTRIES = entries1.size();
	double value;
	for(size_t i = 0; i < 1; ++i)
	{
		const CPUData & e1 = entries1[i];
		const CPUData & e2 = entries2[i];

		std::cout.width(3);

		const float ACTIVE_TIME	= static_cast<float>(GetActiveTime(e2) - GetActiveTime(e1));
		const float IDLE_TIME	= static_cast<float>(GetIdleTime(e2) - GetIdleTime(e1));
		const float TOTAL_TIME	= ACTIVE_TIME + IDLE_TIME;

		std::cout.setf(std::ios::fixed, std::ios::floatfield);
		std::cout.width(6);
		std::cout.precision(2);
		value =(100.f * ACTIVE_TIME / TOTAL_TIME);

		return value;
	}
}

void init(){
    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
        &lastTotalSys, &lastTotalIdle);
    fclose(file);
}

double getCurrentValue(){
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent*100;
}

class RouteGuideClient {
 public:
  RouteGuideClient(std::shared_ptr<Channel> channel, const std::string& db)
      : stub_(RouteGuide::NewStub(channel)) {
   // routeguide::ParseDb(db, &feature_list_);
  }

  void GetStatus(string server, string ip) {
    Input input;
    Stats cpustats;
    input.set_server(server);
    input.set_ip(ip);
    double metrics=getcpustatistics();
    cout<<to_string(metrics);
    input.set_cpumet(to_string(metrics));
    //cout<<"here";
    GetOneCPUStats(input, &cpustats);
  }

  void ListServerslist() {
	  List list;
  		List listR;
  		ClientContext context;
  		std::cout << "Live VMs"
  				<< std::endl;
  		list.set_serverlist("i-024fe56765e22dc3d");
  		std::unique_ptr<ClientReader<List> > reader(
  				stub_->ListServerslist(&context, listR));
  		while (reader->Read(&list)) {
  			cout<<list.serverlist()<<std::endl;
  		}
  		Status grpcStatus = reader->Finish();
  		if (grpcStatus.ok()) {
  			std::cout << "List rpc succeeded." << std::endl;
  		} else {
  			std::cout << "List rpc failed." << std::endl;
  		}
  	}
  void ListServers() {
  		Input inSend;
  		Input inReceive;
  		ClientContext context;
  		std::cout << "Servers list      CPU metrics"
  				<< std::endl;
  		inSend.set_server("i-024fe56765e22dc3d");
  		std::unique_ptr<ClientReader<Input> > reader(
  				stub_->ListServers(&context, inReceive));
  		while (reader->Read(&inSend)) {
  			cout<<inSend.server()<<"  "<<inSend.cpumet()<<"  "<<std::endl;
  		}
  		Status grpcStatus = reader->Finish();
  		if (grpcStatus.ok()) {
  			std::cout << "servers list rpc succeeded." << std::endl;
  		} else {
  			std::cout << "servers list rpc failed." << std::endl;
  		}
  	}

 private:


  bool GetOneCPUStats(const Input& input, Stats* cpustats) {
    ClientContext context;
    Status status = stub_->GetStatus(&context, input, cpustats);
    if (!status.ok()) {
      std::cout << "GetFeature rpc failed." << std::endl;
      return false;
    }
    cout<<cpustats->cpuuse();
    return true;
  }

  std::unique_ptr<RouteGuide::Stub> stub_;
};

int main(int argc, char** argv) {
  std::string db = "";
  string loadbalancerip=argv[4];
  std::cout <<loadbalancerip;
  RouteGuideClient guide(
      grpc::CreateChannel(loadbalancerip+":50051",
                          grpc::InsecureChannelCredentials()),
      db);

  std::cout << "\n-------------- metrics sent --------------" << std::endl;
  if(strcmp(argv[1],"1")==0){
  guide.GetStatus(argv[2],argv[3]);
  }else{
	  guide.ListServers();
	  guide.ListServerslist();
	  cout<<argv[1];
  }
  return 0;
}
