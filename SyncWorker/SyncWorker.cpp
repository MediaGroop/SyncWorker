// SyncWorker.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "easylogging++.h"
#include "FileManager.h"
#include "ConfigLoader.h"
#include "ServVars.h"
#include "Rooming.h"

//Handlers
#include "WorkerConnectHandler.h"
#include "WorkerDisconnectHandler.h"

//RPC's
#include "AddEntityHandler.h"
#include "RemoveEntityHandler.h"
#include "MoveEntityHandler.h"
#include "DeleteEntityHandler.h"
#include "UpdateEntityHandler.h"


#pragma comment(lib, "BulletCollision_Debug.lib")
#pragma comment(lib, "BulletDynamics_Debug.lib")
#pragma comment(lib, "LinearMath_Debug.lib")


//Some of copy-pasted options for logger
#define ELPP_STL_LOGGING
#define ELPP_PERFORMANCE_MICROSECONDS
#define ELPP_LOG_STD_ARRAY
#define ELPP_LOG_UNORDERED_MAP
#define ELPP_UNORDERED_SET
#define ELPP_THREAD_SAFE
//end

//DONT FORGET THIS SHIT!!1
INITIALIZE_EASYLOGGINGPP

//extern vars

//Server instance
Server* mainServer;
//Processors collection
std::map<int, RoomProcessor*> _processors;
//Amount of room processors
int proc_count = 0;
//Worker's rpc
RakNet::RPC4 rpc;
//Entity without rooms
std::map<int, Entity*> _roomless_entities;


using namespace FileManager;

//Configures easyLogging. TODO: adapt for linux systems
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
	listen.add((short)ID_NEW_INCOMING_CONNECTION, handleConnect); // Server connect handler
	listen.add((short)ID_CONNECTION_LOST, handleDisconnect); // Server disconnect handler

	Server srv(&listen);

	mainServer = &srv;
	std::thread trd(mainServer->startNetworkTrd, mainServer, ConfigLoader::getIntVal("Network-Port"), ConfigLoader::getIntVal("Network-MaxCons"));
	mainServer->setThread(&trd);
	mainServer->getPeer()->AttachPlugin(&rpc);

	//Registering RPC's
	rpc.RegisterFunction("ae", handleEntity); // adding entity to room
	rpc.RegisterFunction("me", moveEntity); // moving entity to another room(Can't add to nowhere!)
	rpc.RegisterFunction("re", removeEntity); // removes entity from room(Places it to the roomless)
	rpc.RegisterFunction("de", deleteEntity); // deletes entity
	rpc.RegisterFunction("ue", updateEntity); // updates da entity
	//END

	gets(str);

	mainServer->setRunning(false);
	mainServer->getThread()->join();

	return 0;
}

