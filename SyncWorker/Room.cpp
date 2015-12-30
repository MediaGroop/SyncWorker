#include "Room.h"
#include "easylogging++.h"
#include "BulletCollision\BroadphaseCollision\btDbvtBroadphase.h"
#define USE_PHYSICS false

void Room::removeEntity(int id)
{
	Entity* e = (*_entities.find(id)).second;
	_entities.erase(id);
	_dynamicsWorld->removeRigidBody(e->getBody());
};

float length(Entity* e1, Entity* e2)
{
	return sqrt(pow((e2->getX() - e1->getX()), 2) + pow((e2->getY() - e1->getY()), 2) + pow((e2->getZ() - e1->getZ()), 2));
}

//Recalculating distances in rooms. TODO: make it with physics?? 
void Room::step()
{
	if (!USE_PHYSICS){
		float l = 0;
		for (std::map<int, Entity*>::iterator i = this->getEntities()->begin(); i != this->getEntities()->end(); ++i)
		{
			for (std::map<int, Entity*>::iterator i2 = this->getEntities()->begin(); i2 != this->getEntities()->end(); ++i2)
			{
				l = length((*i).second, (*i2).second);
				if (l > (*i).second->getRadius()){
					(*i).second->removeNear((*i2).second);
				}
				else if (l <= (*i).second->getRadius())
				{
					(*i).second->addNear((*i2).second);
				}
			}
		}
	}
	else{
		this->_dynamicsWorld->stepSimulation(1.f / 60.f, 10.0f);
		int numManifolds = _dynamicsWorld->getDispatcher()->getNumManifolds();
		for (int i = 0; i<numManifolds; i++)
		{
			btPersistentManifold* contactManifold = _dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
			int numContacts = contactManifold->getNumContacts();
			if (numContacts > 0)
			{
				const btCollisionObject* obA = contactManifold->getBody0();
				const btCollisionObject* obB = contactManifold->getBody1();
				//TODO: finish it...
			}
		}
	}
}

void Room::addEntity(Entity* e)
{
	_entities.insert(std::pair<int, Entity*>(e->getId(), e));
	_dynamicsWorld->addRigidBody(e->getBody());
};


Room::Room(int i)
{
	this->_id = i;
	this->_collisionConfiguration = new btDefaultCollisionConfiguration();
	this->_dispatcher = new btCollisionDispatcher(this->_collisionConfiguration);
	this->_overlappingPairCache = new btDbvtBroadphase();
	this->_solver = new btSequentialImpulseConstraintSolver;
	this->_dynamicsWorld = new btDiscreteDynamicsWorld(this->_dispatcher, this->_overlappingPairCache, this->_solver, this->_collisionConfiguration);
	this->_dynamicsWorld->setGravity(*new btVector3(0, 0, 0));	
}



Room::~Room()
{
}
