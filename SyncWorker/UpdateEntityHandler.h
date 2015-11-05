#pragma once
#include "stdafx.h"
#include "Rooming.h"

//Updates entity position
void updateEntity(RakNet::BitStream *bitStream, RakNet::Packet *p){
	int offset = bitStream->GetReadOffset();
	int entityId, roomId;
	Entity* ent_ptr;
	Room* fRoom;
	float x, y, z;
	bitStream->Read(entityId);
	bitStream->Read(roomId);

	bitStream->Read(x);
	bitStream->Read(y);
	bitStream->Read(z);

	for (std::map<int, RoomProcessor*>::iterator i = _processors.begin(); i != _processors.end(); ++i)
	{
		fRoom = (*i).second->getRoom(roomId);
		if (fRoom != nullptr)
		{
			break;
		}
	}
	if (fRoom != nullptr)
	{
		Entity* e = fRoom->getEntities()->find(entityId)->second;
		e->setPosition(x, y, z);
	}
}