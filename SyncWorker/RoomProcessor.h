#pragma once
#include <map>
#include "Room.h"

class RoomProcessor
{
private:
	// limit of clients, when reached, processor can't be added any more rooms to sync
	int maxClients = 2000;
	std::map<int, Room*> _rooms;
	std::thread* _trd;
	bool _running;
public:

	Room* getRoom(int id){
		return _rooms[id];
	};

	int getClientsCount()
	{
		int a = 0;
		for (std::map<int, Room*>::iterator i = getRooms()->begin(); i != getRooms()->end(); ++i)
		{
			a += (*i).second->getEntitiesCount();
		}
		return a;
	};

	bool getRunning(){
		return _running;
	};

	std::map<int, Room*>* getRooms(){
		return &_rooms;
	}

	RoomProcessor();
	RoomProcessor(int);
	~RoomProcessor();
	bool addRoom(Room*);
	bool removeRoom(int);
};

