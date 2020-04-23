#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include <list>
#ifdef BAZEL_BUILD
#include "examples/protos/route_guide.grpc.pb.h"
#else
#include "route_guide.grpc.pb.h"
#endif

using namespace std;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using std::chrono::system_clock;
using routeguide::Input;
using routeguide::Stats;
using routeguide::RouteGuide;
//using routeguide::GetStatus;

struct square {
	string serverID;
	string ip;
	string cpu_metric;
	int status;
} square;
list<struct square> workingset;
std::queue<string> Qservers;
std::queue<string> Rservers;
string Qserver;
static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
string loadBalancerIP;
int checkForThreshold(){
	struct square temp;
	for(auto it = workingset.begin(); it != workingset.end(); ++it){
		double cpu_metrics = atof(((*it).cpu_metric).c_str());
		if(cpu_metrics>0.0){
			return 0;
		}
	}
	//	cout<<get_current_dir()<<"\n";
	return 1;
}
void addServersQueue(){
	Qservers.push("i-09a734a7f49469fed");
}
string getFromQ(){
	string serverIDQueue = Qservers.front();
	return serverIDQueue;
}

int newServer(){
string command = "./check.sh";
string serverIdFromQ = getFromQ();
command = command +" "+ serverIdFromQ+" "+loadBalancerIP;;
system(command.c_str());
}

int addServer(string serverId, string serverIp, string servercpumet){
	struct square temp;
	for(auto it = workingset.begin(); it != workingset.end(); ++it){
		if((*it).serverID==serverId){
			(*it).ip=serverIp;
			(*it).cpu_metric=servercpumet;
			(*it).status=checkForThreshold();
			if((*it).status  == 0){
				newServer();
			}
			return 2;
		}
	}
	temp.serverID=serverId;
	temp.ip=serverIp;
	temp.cpu_metric=servercpumet;
    temp.status=checkForThreshold();
	workingset.push_front(temp);
	//system("./check.sh ");
	return 3;
	//	cout<<get_current_dir()<<"\n";
}

class RouteGuideImpl final : public RouteGuide::Service {
 public:
  explicit RouteGuideImpl(const std::string& db) {
    //routeguide::ParseDb(db, &feature_list_);
  }

  Status GetStatus(ServerContext* context, const Input* input,
                    Stats* cpustats) override {
	  addServer(input->server(), input->ip(), input->cpumet());
	  newServer();
      return Status::OK;
  }

  Status ListServers(ServerContext* context, const Input* input,
			ServerWriter<Input>* writer) override {
	  Input inputLoop;
		for(auto it = workingset.begin(); it != workingset.end(); ++it){
			inputLoop.set_server((*it).serverID);
			inputLoop.set_ip((*it).ip);
			inputLoop.set_cpumet((*it).cpu_metric);
			inputLoop.set_status((*it).status);
			const Input& inputLoopin = inputLoop;
			writer->Write(inputLoopin);
		}
		return Status::OK;
	}
};

void RunServer(const std::string& db_path) {
  std::string server_address("0.0.0.0:50051");
  RouteGuideImpl service(db_path);

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  // Expect only arg: --db_path=path/to/route_guide_db.json.
  std::string db = "";
  loadBalancerIP=argv[1];
  addServersQueue();
  RunServer(db);

  return 0;
}
