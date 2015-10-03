// SyncWorker.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include "easylogging++.h"
#include "FileManager.h"
#include "ConfigLoader.h"
#include "ServVars.h"

#define ELPP_STL_LOGGING
#define ELPP_PERFORMANCE_MICROSECONDS
#define ELPP_LOG_STD_ARRAY
#define ELPP_LOG_UNORDERED_MAP
#define ELPP_UNORDERED_SET
#define ELPP_THREAD_SAFE

//DONT FORGET THIS SHIT!!1
INITIALIZE_EASYLOGGINGPP

//extern vars
Server* mainServer;
std::map<int, Room*> _rooms;
RakNet::RPC4 rpc;
using namespace FileManager;

//Configures easyLogging
void setupLog(){
	time_t t;
	t = time(0);
	char str[64];

	getcwd(str, 64);
	if (!FileManager::DirExists(strcat(str, "\\logs\\"))){
		mkdir(str);
	}

	std::string log_name = "logs\\";
	log_name.append(asctime(localtime(&t)));
	log_name[log_name.length() - 1] = ' ';
	log_name.append(".txt");

	for (int i = 0; i < log_name.length(); ++i)
	{
		if (log_name[i] == ':' || log_name[i] == ' ' || log_name[i] == '\r')
		{
			log_name[i] = '_';
		}
	}

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, log_name);
}


int _tmain(int argc, _TCHAR* argv[])
{
	char str[10];
	setupLog();
	ConfigLoader::init("config.ini");
	NetworkListener listen;
	//listen.add((short)ID_NEW_INCOMING_CONNECTION, handleconn); // Server connect handler
	//listen.add((short)ID_CONNECTION_LOST, handledisconn); // Server disconnect handler

	Server srv(&listen);

	mainServer = &srv;
	std::thread trd(mainServer->startNetworkTrd, mainServer, ConfigLoader::getIntVal("Network-Port"), ConfigLoader::getIntVal("Network-MaxCons"));
	mainServer->setThread(&trd);
	mainServer->getPeer()->AttachPlugin(&rpc);

	//Registering RPC's
	//rpc.RegisterSlot("lw", loadWorldsRPC, 0);
	//END

	gets(str);

	mainServer->setRunning(false);
	mainServer->getThread()->join();

	return 0;
}

