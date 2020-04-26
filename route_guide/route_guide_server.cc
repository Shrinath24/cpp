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
using routeguide::List;
//using routeguide::GetStatus;

struct square {
	string serverID;
	string ip;
	string cpu_metric;
	int status;
} square;
list<struct square> workingset;
std::queue<string> Qservers;
std::queue<string> Lservers;
std::queue<string> l1servers;
string Qserver;
static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
string loadBalancerIP;
int checkForThreshold(){
	int flag=0;
	struct square temp;
	for(auto it = workingset.begin(); it != workingset.end(); ++it){
			double cpu_metrics = atof(((*it).cpu_metric).c_str());
			if(cpu_metrics>30.0){
				flag=1;
				break;
			}else{
				flag=0;
			}
		}
	for(auto it = workingset.begin(); it != workingset.end(); ++it){
		double cpu_metrics = atof(((*it).cpu_metric).c_str());
		if(cpu_metrics>70.0){
			return 0;
		}else if(Lservers.size()>2 && flag==0){
			return 2;
		}
	}
	//	cout<<get_current_dir()<<"\n";
	return 1;
}
void addServersQueue(){
	//Qservers.push("i-09a734a7f49469fed");
	Qservers.push("2");
	Lservers.push("1");
	Qservers.push("3");
	Qservers.push("4");
	Qservers.push("5");
}
void writeFile(string content){
ofstream myfile ("ip-list.txt");
  if (myfile.is_open()){
    myfile << content;
    myfile.close();
  }
  else cout << "Unable to open file";
}
string getFromQ(){
	string serverIDQueue = Qservers.front();
	Lservers.push(serverIDQueue);
	Qservers.pop();
	string content;
	while (!Lservers.empty()){
				content+=Lservers.front()+",";

				l1servers.push(Lservers.front());
				Lservers.pop();
			}
			while (!l1servers.empty()){
			//	cout<<" "<<l1servers.front();
				Lservers.push(l1servers.front());
				l1servers.pop();
	}
	writeFile(content);
	return serverIDQueue;
}

string getFromQDown(){
	string serverIDQueue = Lservers.front();
	Qservers.push(serverIDQueue);
	Lservers.pop();
	string content;
	while (!Lservers.empty()){
				content+=Lservers.front()+",";
				l1servers.push(Lservers.front());
				Lservers.pop();
			}
			while (!l1servers.empty()){
			//	cout<<" "<<l1servers.front();
				Lservers.push(l1servers.front());
				l1servers.pop();
	}
	return serverIDQueue;
}
int delServer(){
	string command = "./check_down1.sh";
	string serverIdFromQ = getFromQDown();
	command = command +" "+ serverIdFromQ;
	system(command.c_str());
}



int newServer(){
	string command = "./check1.sh";
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
			}else if((*it).status  == 2){
				delServer();
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
		return Status::OK;
	}

	Status ListServers(ServerContext* context, const Input* input,
			ServerWriter<Input>* writer) override {
		Input inputLoop;
		for(auto it = workingset.begin(); it != workingset.end(); ++it){
			while (!Lservers.empty()){
				if(Lservers.front().compare((*it).serverID)==0){
				inputLoop.set_server((*it).serverID);
				inputLoop.set_ip((*it).ip);
				inputLoop.set_cpumet((*it).cpu_metric);
				inputLoop.set_status((*it).status);
				const Input& inputLoopin = inputLoop;
				writer->Write(inputLoopin);
				}
				l1servers.push(Lservers.front());
				Lservers.pop();
			}
			while (!l1servers.empty()){
			//	cout<<" "<<l1servers.front();
				Lservers.push(l1servers.front());
				l1servers.pop();
			}
		}
		return Status::OK;
	}
	Status ListServerslist(ServerContext* context, const List* list,
			ServerWriter<List>* writer) override {
		List listLoop;
		while (!Lservers.empty()){
			listLoop.set_serverlist(Lservers.front());
			const List& listLoopin = listLoop;
			writer->Write(listLoopin);
			l1servers.push(Lservers.front());
			Lservers.pop();
		}
		while (!l1servers.empty()){
		//	cout<<" "<<l1servers.front();
			Lservers.push(l1servers.front());
			l1servers.pop();
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
