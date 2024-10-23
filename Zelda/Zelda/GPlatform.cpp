#include "pch.h"
#include "GPlatform.h"

#include "Collider.h"
#include "GRigidBody.h"

#include "CEngine.h"

GPlatform::GPlatform() :
	m_Collider(),
	m_RigidBody()
{
	m_Collider = AddComponent<Collider>();
	m_Collider->SetName(L"Platform_Collider");
	m_Collider->SetScale(Vec2(800, 100));

	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetRigidBodyType(RIGIDBODY_TYPE::STATIC);
	m_RigidBody->SetName(L"Platform_RigidBody");
}

GPlatform::~GPlatform()
{

}

void GPlatform::Begin()
{
}

void GPlatform::Tick()
{
}

void GPlatform::Render()
{
}


