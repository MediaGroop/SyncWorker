#pragma once
#include <map>
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
	
	void removeNear(Entity* e);

	void addNear(Entity* e);

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

