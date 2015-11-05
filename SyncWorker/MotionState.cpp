#include "stdafx.h"
#include "MotionState.h"

MotionState::MotionState(Entity* e) : _entity(e)
{
};


MotionState::~MotionState()
{
};

void MotionState::setWorldTransform(const btTransform& worldTrans)
{
	_entity->getTransform()->operator=(worldTrans);
};

void MotionState::getWorldTransform(btTransform& worldTrans) const
{
	worldTrans = *_entity->getTransform();
};