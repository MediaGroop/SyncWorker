#pragma once
#include <map>
#include "Entity.h"
#include <thread>

class Room
{
private:
	std::map<int, Entity> _entities; 
	
	int _id;
	std::thread* _trd;
	bool _running;
public:
	void removeEntity(int);
	void addEntity(Entity*);
	Room(int i);
	~Room();

	bool getRunning(){
		return _running;
	};

	std::map<int, Entity>* getEntities(){
		return &_entities;
	};
};