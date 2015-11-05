#pragma once
#include <map>
#include "Entity.h"
#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"
#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"
#include "BulletCollision\CollisionDispatch\btDefaultCollisionConfiguration.h"
#include <thread>

class Room
{
private:
	std::map<int, Entity*> _entities; 
	
	btDefaultCollisionConfiguration* _collisionConfiguration;
	btCollisionDispatcher* _dispatcher;
	btBroadphaseInterface* _overlappingPairCache;
	btSequentialImpulseConstraintSolver* _solver;
	btDiscreteDynamicsWorld* _dynamicsWorld;
	
	int _id;

public:
	int getId(){
		return _id;
	}

	int getEntitiesCount()
	{
		int a = 0;
		for (std::map<int, Entity*>::iterator i = this->getEntities()->begin(); i != this->getEntities()->end(); ++i)
		{
			++a;
		}
		return a;
	}

	void step();
	void removeEntity(int);
	void addEntity(Entity*);
	Room(int i);
	~Room();


	std::map<int, Entity*>* getEntities(){
		return &_entities;
	};
};