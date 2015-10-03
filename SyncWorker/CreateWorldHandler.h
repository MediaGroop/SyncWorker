#pragma once
#include "stdafx.h"
#include "ServVars.h"

void handleCreateWorld(RakNet::Packet* p)
{

	RakNet::BitStream bsIn(p->data, p->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	
	int id;
	float x, y, z;

	bsIn.Read(id);
	bsIn.Read(x);
	bsIn.Read(y);
	bsIn.Read(z);

	_rooms.insert(pair<int, Room*>(id, new Room(id)));
};