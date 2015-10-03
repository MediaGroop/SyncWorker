#include "Entity.h"


Entity::Entity(int id, int wId, float radius) : _id(id), _room(wId), _radius(radius)
{
};

Entity::~Entity()
{
	
};


Entity* Entity::setPosition(float x, float y, float z){
	_x = x;
	_y = y;
	_z = z;
};
