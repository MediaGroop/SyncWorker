#include "stdafx.h"
#include "RoomProcessor.h"
#define sleep Sleep(10);

void step(RoomProcessor* a){
	while (a->getRunning()){
		sleep
		for (std::map<int, Room*>::iterator i = a->getRooms()->begin(); i != a->getRooms()->end(); ++i)
		{
			(*i).second->step();
		}
	}
}

RoomProcessor::RoomProcessor() : RoomProcessor(2000)
{
}

RoomProcessor::RoomProcessor(int a) : maxClients(a)
{
	this->_running = true;
	this->_trd = new std::thread(step, this);
}


RoomProcessor::~RoomProcessor()
{

}

bool RoomProcessor::addRoom(Room* r){
	if ((*_rooms.find(r->getId())).second == nullptr && getClientsCount() < maxClients) {
		_rooms.insert(pair<int, Room*>(r->getId(), r));
		return true;
	}
	return false;
};

bool RoomProcessor::removeRoom(int i){
	if ((*_rooms.find(i)).second != nullptr) {
		_rooms.erase(i);
		return true;
	}
	return false;
};
