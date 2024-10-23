#include "pch.h"
#include "GRigidBody.h"

GRigidBody::GRigidBody() :
	Component(COMPONENT_TYPE::RIGIDBODY),
	m_RigidBodyType(RIGIDBODY_TYPE::DYNAMIC),
	m_Force(),
	m_Velocity(),
	m_Mass(1.f),
	m_Friction(0.f),
	m_Gravity(Vec2(0.f, 0.f))
	//m_Elasticity(1.f)
{
}

GRigidBody::~GRigidBody()
{

}

void GRigidBody::CalGravity()
{
	m_Velocity += m_Gravity * DT;
}

void GRigidBody::CalFriction()
{
	// ¸¶Âû·Â
	float Speed = m_Velocity.Length();
	if (0 != Speed)
	{
		Speed -= m_Friction * m_Mass * DT;
		if (Speed < 0)
			Speed = 0;

		m_Velocity = m_Velocity.Normalize() * Speed;
	}
}

void GRigidBody::FinalTick()
{
	if (m_RigidBodyType == RIGIDBODY_TYPE::STATIC)
	{
		m_Velocity = Vec2(0.f, 0.f);
		return;
	}

	// Èû
	Vec2 Accel = m_Force / m_Mass;
	m_Velocity += Accel * DT;

	CalGravity();

	CalFriction();

	// ¼³Á¤
	Vec2 OwnerPos = GetOwner()->GetPos();
	OwnerPos += m_Velocity * DT;
	GetOwner()->SetPos(OwnerPos);

	// Èû ÃÊ±âÈ­
	m_Force = Vec2(0.f, 0.f);
}
