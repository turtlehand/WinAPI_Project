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
	virtual void Awake() override;			// ������ ���۵� ��
	virtual void Begin() override;
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	virtual void InteractionEffect_Element(GCreature* _Creature);

public:
	void SetVelocity(Vec2 _Velocity);
	Vec2 GetVelocity() { return m_Velocity; }

public:
	GArrow();
	virtual ~GArrow() override;
};

