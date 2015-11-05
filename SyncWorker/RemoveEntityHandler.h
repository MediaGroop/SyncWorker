#pragma once
#include "stdafx.h"
#include "Rooming.h"

//Removes entity from it's room and places it to the roomless list
void removeEntity(RakNet::BitStream *bitStream, RakNet::Packet *p)
{
	int offset = bitStream->GetReadOffset();
	int entityId, roomId;
	Entity* ent_ptr;
	Room* fRoom;

	bitStream->Read(entityId);
	bitStream->Read(roomId);

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
		fRoom->removeEntity(entityId);
		_roomless_entities.insert(pair<int, Entity*>(e->getId(), e));
	}
}