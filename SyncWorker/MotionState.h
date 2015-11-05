#pragma once
#include "LinearMath\btMotionState.h"
#include "Entity.h"

class MotionState :
	public btMotionState
{
private:
	Entity* _entity;
public:
	MotionState(Entity*);
	~MotionState();

	virtual void getWorldTransform(btTransform& worldTrans) const override;

	virtual void setWorldTransform(const btTransform& worldTrans) override;


};

