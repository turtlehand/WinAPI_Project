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
	virtual void Awake() override;			// 레벨이 시작될 때
	//virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

public:
	virtual void DropItem() override;

public:
	GLog();
	virtual ~GLog() override;
};

