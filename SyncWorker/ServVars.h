#pragma once
#include "stdafx.h"
#include "Server.h"
#include <map>
#include "Room.h"
#include "RPC4Plugin.h"
//#region vars
extern Server* mainServer;
extern std::map<int, Room*> _rooms;
extern RakNet::RPC4 rpc;
//#endregion