#include "Entity.h"
#include "BulletCollision\CollisionShapes\btSphereShape.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "MotionState.h"

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
