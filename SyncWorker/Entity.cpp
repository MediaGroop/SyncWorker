#include "Entity.h"
#include "BulletCollision\CollisionShapes\btSphereShape.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "MotionState.h"
#include "ServVars.h"

Entity::Entity(int id, int wId, float radius) : _id(id), _room(wId), _radius(radius)
{
	btSphereShape* s = new btSphereShape(radius);
	_body = new btRigidBody(0, new MotionState(this), s);
	
	_body->setCollisionFlags(_body->getCollisionFlags() |
		btCollisionObject::CF_NO_CONTACT_RESPONSE |
		btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

};

Entity::~Entity()
{
	
};


Entity* Entity::setPosition(float x, float y, float z){
	return this->setPosition(*new btVector3(x, y, z));
};

Entity* Entity::setPosition(btVector3& pos){
	this->_transform.setOrigin(pos);
	_body->setWorldTransform(_transform);
	return this;
};

void Entity::removeNear(Entity* e){
	auto i = _entities.find(e->getId());
	if (i->second != NULL){
		_entities.erase(i);
		RakNet::BitStream bs;
		bs.Write(this->getRoom()); // room id
		bs.Write(this->getId()); // from what entity
		bs.Write(e->getId()); // entId to remove
		rpc.Call("rn", &bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, mainServer->getPeer()->GetSystemAddressFromIndex(0), true);

	}
};

void Entity::addNear(Entity* e){
	auto i = _entities.find(e->getId());
	if (i->second == NULL){
		_entities.insert(std::pair<int, Entity*>(e->getId(), e));
		RakNet::BitStream bs;
		bs.Write(this->getRoom()); // room id
		bs.Write(this->getId()); // to what entity
		bs.Write(e->getId()); // entId to add
		rpc.Call("an", &bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, mainServer->getPeer()->GetSystemAddressFromIndex(0), true);
	}

};