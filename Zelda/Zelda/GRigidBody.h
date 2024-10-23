#pragma once
#include "GComponent.h"

class GRigidBody :
	public GComponent
{
private:
	RIGIDBODY_TYPE	m_RigidBodyType;		// ������ٵ� Ÿ��
	Vec2			m_Force;				// ��
	Vec2			m_Velocity;				// �ӵ�
	float			m_Mass;					// ����
	float			m_Friction;				// ������
	Vec2			m_Gravity;				// �߷�
	//float			m_Elasticity;			// ź�� : ź���� 1���� Ŭ �� ������ 0���� ���� �� ����.

public:

	void SetRigidBodyType(RIGIDBODY_TYPE _RigidBodyType) { m_RigidBodyType = _RigidBodyType; }
	RIGIDBODY_TYPE GetRigidBodyType() { return m_RigidBodyType; }

	void AddForce(Vec2 _Force) { m_Force += _Force; }
	
	void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
	void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }
	Vec2 GetVelocity() { return m_Velocity; }

	void SetMass(float _Mass) { m_Mass = _Mass; }
	float GetMass() { return m_Mass; }

	void SetFriction(float _Friction) { m_Friction = _Friction; }
	float GetFriction() { return m_Friction; }

	void SetGravity(Vec2 _Gravity) { m_Gravity = _Gravity; }
	Vec2 GetGravity() { return m_Gravity; }

	//void SetElasticity(float _Elasticity) { m_Elasticity = _Elasticity; }
	//float GetElasticity() { return m_Elasticity; }

private:
	void CalGravity();
	void CalFriction();

public:
	virtual void FinalTick() override;

public:
	GRigidBody();
	virtual ~GRigidBody() override;

};

