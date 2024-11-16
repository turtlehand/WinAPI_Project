#pragma once
#include "CObj.h"
#include "GHitBox.h"
#include "GRigidBody.h"

class GRigidBody;
class GBoxCollider;
class GCollider;

class GArrow :
	public GHitBox
{
private:
	GRigidBody* m_RigidBody;
	Vec2 m_Velocity;

public:
	virtual void Awake() override;			// 레벨이 시작될 때
	virtual void Begin() override;
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

	virtual void InteractionEffect_Element(GCreature* _Creature);

public:
	void SetVelocity(Vec2 _Velocity);
	Vec2 GetVelocity() { return m_Velocity; }

public:
	GArrow();
	virtual ~GArrow() override;
};

