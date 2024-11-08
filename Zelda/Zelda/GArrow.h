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
	virtual void Begin() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

	//virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	void SetVelocity(Vec2 _Velocity) { m_Velocity =_Velocity; }
	Vec2 GetVelocity() { return m_Velocity; }

public:
	GArrow();
	virtual ~GArrow() override;
};

