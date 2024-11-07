#include "pch.h"
#include "GArrow.h"

#include "GRigidBody.h"

#include "CSelectGDI.h"
#include "DeBugRenderManager.h"
#include "GCamera.h"

#include"GBoxCollider.h"

GArrow::GArrow() :
	m_RigidBody(nullptr)
{
	m_RigidBody = AddComponent<GRigidBody>();
}

GArrow::~GArrow()
{
}

void GArrow::Begin()
{
	GHitBox::Begin();
}

void GArrow::Tick()
{
	GHitBox::Tick();
	m_RigidBody->SetVelocity(m_Velocity);
}


void GArrow::Render()
{
	GHitBox::Render();
}

