#pragma once
#include <map>
#include "ServVars.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"

class Entity
{
private:
	int _id;
	int _room;

	float _x, _y, _z;
	float _radius;

	btTransform _transform;
	btRigidBody* _body;

	std::map<int, Entity*> _entities;

public:

	btTransform* getTransform()
	{
		return &_transform;
	}
	
	btRigidBody* getBody()
	{
		return _body;
	}

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
			bs.Write(this->getId()); // from what entity
			bs.Write(e->getId()); // entId to remove
			rpc.Signal("rn", &bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, mainServer->getPeer()->GetSystemAddressFromIndex(0), false, true);

		}
	};

	void addNear(Entity* e){
		auto i = _entities.find(e->getId());
		if (i->second == NULL){
			_entities.insert(std::pair<int, Entity*>(e->getId(), e));
			RakNet::BitStream bs;
			bs.Write(this->getRoom()); // room id
			bs.Write(this->getId()); // to what entity
			bs.Write(e->getId()); // entId to add
			rpc.Signal("an", &bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, mainServer->getPeer()->GetSystemAddressFromIndex(0), false, true);
		}
	
	};

	Entity(int, int, float);
	
	~Entity();
	
	Entity* setPosition(float, float, float);

	Entity* setPosition(btVector3&);

	int getRoom()
	{
		return _room;
	}

	int getId()
	{
		return _id;
	}

};

