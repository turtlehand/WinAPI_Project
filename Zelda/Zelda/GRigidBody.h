#pragma once
#include "GComponent.h"

class GRigidBody :
	public GComponent
{
private:
	RIGIDBODY_TYPE	m_RigidBodyType;		// 리지드바디 타입
	Vec2			m_Force;				// 힘
	Vec2			m_Velocity;				// 속도
	float			m_Mass;					// 무게
	float			m_Friction;				// 마찰력
	Vec2			m_Gravity;				// 중력
	//float			m_Elasticity;			// 탄성 : 탄성은 1보다 클 수 없으며 0보다 작을 수 없다.

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

