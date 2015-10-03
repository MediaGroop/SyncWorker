#include "Room.h"
#include "easylogging++.h"

#define sleep Sleep(10)

void Room::removeEntity(int id)
{
	Entity* e = &((*_entities.find(id)).second);
	_entities.erase(id);
	delete e;
};

float length(Entity* e1, Entity* e2)
{
	return sqrt( pow((e2->getX() - e1->getX()), 2) + pow((e2->getY() - e1->getY()), 2) + pow((e2->getZ() - e1->getZ()), 2));
}

void step(Room* w, long delay)
{

	while (w->getRunning()){
		//	LOG(INFO) << "step";
		float l = 0;
		sleep;
		for (std::map<int, Entity>::iterator i = w->getEntities()->begin(); i != w->getEntities()->end(); ++i)
		{
			for (std::map<int, Entity>::iterator i2 = w->getEntities()->begin(); i2 != w->getEntities()->end(); ++i2)
			{
				l = length(&(*i).second, &(*i2).second);
				if (l > (*i).second.getRadius()){
					(*i).second.removeNear(&(*i2).second);
				}
				else if (l <= (*i).second.getRadius())
				{
					(*i).second.addNear(&(*i2).second);
				}
			}
		}
	}
}

void Room::addEntity(Entity* e)
{
	_entities.insert(std::pair<int, Entity>(e->getId(), *e));
};

Room::Room(int i)
{
	this->_id = i;
	this->_running = true;
	this->_trd = new std::thread(step, this, 100);
}



Room::~Room()
{
}
