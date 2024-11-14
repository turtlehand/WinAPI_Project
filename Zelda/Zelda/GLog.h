#pragma once
#include "GCreature.h"

class GBoxCollider;
class GSpriteRenderer;
class GRigidBody;

class GLog :
    public GCreature
{
	GRigidBody* m_RigidBody;
	GSpriteRenderer* m_Sprite;

public:
	virtual void DropItem();

public:
	virtual void Begin() override;			// 레벨이 시작될 때
	//virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기


public:
	GLog();
	virtual ~GLog() override;
};

