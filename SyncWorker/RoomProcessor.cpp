#include "stdafx.h"
#include "RoomProcessor.h"

void step(RoomProcessor* a){
#if defined(_WIN64) || defined(_WIN32)
#else
  	struct timespec req;
	req.tv_sec = 0;
	req.tv_nsec = 25000L;
#endif
	while (a->getRunning()){
	  #if defined(_WIN64) || defined(_WIN32)
		Sleep(10);
#else
		nanosleep(&req, NULL);
#endif
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
		_rooms.insert(std::pair<int, Room*>(r->getId(), r));
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
