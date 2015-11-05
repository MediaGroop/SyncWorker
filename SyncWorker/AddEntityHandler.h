#pragma once
#include "stdafx.h"
#include "Rooming.h"
/*																				____________________
																				   \__________/    |
"Add entity" packet structure:														|  C++    |    |
- Room  id: id of a room that entity mst be spawned in(Integer)                /------------------|\
- Entity id: entity unique id(Integer)                                         /                   |\\
- X: x pos(Float)                                                             /   /===+      /===+ O \\
- Y: y pos(Float)                                                             |  /00  |     /00  |   ||
- Z: z pos(Float)                                                             |  \0---/     \0---/   ||
- Radius: radius of sync(float)                                               |                      ||
                                                                              |   \---------------|  ||
                                                                              |    \=========     /  ||
                                                                               \     \-----------/   /
                           													    \___________________/
*/
void handleEntity(RakNet::BitStream *bitStream, RakNet::Packet *p)
{


	int offset = bitStream->GetReadOffset();
	//RakNet::BitStream bsIn(p->data, p->length, false);
	//bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

	int roomId, entId;
	float x, y, z, radius;

	bitStream->Read(roomId);
	bitStream->Read(entId);
	bitStream->Read(x);
	bitStream->Read(y);
	bitStream->Read(z);
	bitStream->Read(radius);
	Room* r;

	for (std::map<int, RoomProcessor*>::iterator i = _processors.begin(); i != _processors.end(); ++i)
	{
		r = (*i).second->getRoom(roomId);
		if (r != nullptr)
		{
			break;
		}
	}

	if (r != nullptr)
	{
		Entity e = *new Entity(entId, roomId, radius);
		r->addEntity(e.setPosition(x, y, z));
	}
	else{
		LOG(INFO) << "No room with such id! So create one";
		Room* newRoom = new Room(roomId);
		bool added = false;

		for (std::map<int, RoomProcessor*>::iterator i = _processors.begin(); i != _processors.end(); ++i)
		{
			if ((*i).second->addRoom(newRoom)){
				added = true;
				break;
			}
		}

		LOG(INFO) << "All processors are busy! So create new";
		if (added = false){
			RoomProcessor* proc = new RoomProcessor();
			++proc_count;
			_processors.insert(pair<int, RoomProcessor*>(proc_count, proc));
			proc->addRoom(newRoom);
		}
	}
};