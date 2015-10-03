#pragma once
#include "stdafx.h"
#include "ServVars.h"
/*																				____________________
																				   \__________/    |
"Add entity" packet structure:														|  C++    |    |
- Room  id: id of a room  that entity mst be spawned in(Integer)                /------------------|\
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
void handleEntity(RakNet::Packet* p)
{

	RakNet::BitStream bsIn(p->data, p->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

	int roomId, entId;
	float x, y, z, radius;


	bsIn.Read(roomId);
	bsIn.Read(entId);
	bsIn.Read(x);
	bsIn.Read(y);
	bsIn.Read(z);
	bsIn.Read(radius);
	
	Room* w = ((_rooms.find(roomId))->second);

	if (w != nullptr)
	{
		Entity e = *new Entity(entId, roomId, radius);
		w->addEntity(e.setPosition(x, y, z));
	}
	else
		LOG(INFO) << "No room with such id!";
};