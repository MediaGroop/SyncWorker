#pragma once
#include "stdafx.h"
#include "Rooming.h"

void moveEntity(RakNet::BitStream *bitStream, RakNet::Packet *p)
{

	int offset = bitStream->GetReadOffset();
	int entityId, roomId, targetRoomId;
	Entity* ent_ptr;
	Room* fRoom;
	Room* tRoom;
	bitStream->Read(entityId);
	bitStream->Read(roomId);
	bitStream->Read(targetRoomId);
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
		for (std::map<int, RoomProcessor*>::iterator i = _processors.begin(); i != _processors.end(); ++i)
		{
			tRoom = (*i).second->getRoom(targetRoomId);
			if (tRoom != nullptr)
			{
				break;
			}
		}
		if (tRoom != nullptr)
		{
			ent_ptr = fRoom->getEntities()->find(entityId)->second;
			if (ent_ptr != nullptr)
			{
				tRoom->addEntity(ent_ptr);
				fRoom->removeEntity(ent_ptr->getId());
			}
			else
			{

				LOG(INFO) << "There's no entity with given id!( Tis mesag can appeer )";
			}
		}
		else
		{
			LOG(INFO) << "Target room is unavailable!( Tis messag must neva appeer )";
		}
	}
	else
	{
		LOG(INFO) << "Source room is unavailable!( Tis messag must neva appeer )";
	}

}