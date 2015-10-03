#pragma once
#include <map>
#include "ServVars.h"

class Entity
{
private:
	int _id;
	int _room;
	float _x, _y, _z;
	float _radius;
	std::map<int, Entity*> _entities;
public:

	float getX()
	{
		return _x;
	}

	float getY()
	{
		return _y;
	}

	float getZ()
	{
		return _z;
	}

	float getRadius(){
		return _radius;
	}
	
	void removeNear(Entity* e){
		auto i = _entities.find(e->getId());
		if (i->second != NULL){
			_entities.erase(i);
			RakNet::BitStream bs;
			bs.Write(this->getRoom()); // room id
			bs.Write(this->getId()); // to what entity
			bs.Write(e->getId()); // to add
			rpc.Signal("re", &bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, mainServer->getPeer()->GetSystemAddressFromIndex(0), false, true);

		}
	};

	void addNear(Entity* e){
		auto i = _entities.find(e->getId());
		if (i->second == NULL){
			_entities.insert(std::pair<int, Entity*>(e->getId(), e));
			RakNet::BitStream bs;
			bs.Write(this->getRoom()); // room id
			bs.Write(this->getId()); // to what entity
			bs.Write(e->getId()); // to add
			rpc.Signal("ae", &bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, mainServer->getPeer()->GetSystemAddressFromIndex(0), false, true);
		}
	
	};

	Entity(int, int, float);
	~Entity();
	Entity* setPosition(float, float, float);

	int getRoom()
	{
		return _room;
	}

	int getId()
	{
		return _id;
	}

};

