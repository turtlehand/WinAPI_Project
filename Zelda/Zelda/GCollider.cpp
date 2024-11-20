#include "pch.h"
#include "GCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "GCamera.h"

#include "GRigidBody.h"

GCollider::GCollider(COLLIDER_TYPE _Type) :
	GComponent(COMPONENT_TYPE::COLLIDER),
	m_ColliderType(_Type),
	m_Offset(),
	m_OverlapCount(0),
	m_Trigger(false),
	m_IsRigidBody(false)
{
}

GCollider::~GCollider()
{
	
}

void GCollider::Awake()
{
	GRigidBody* RigidBody = GetOwner()->GetComponent<GRigidBody>();
	if (RigidBody == nullptr)
		return;

	m_IsRigidBody = true;
}

void GCollider::FinalTick()
{
	// Collider 등록하기

	LAYER_TYPE LayerType = GetOwner()->GetLayerType();
	CLevelMgr::GetInst()->GetCurrentLevel()->RegisterCollider(this, LayerType);
}

void GCollider::OnCollisionEnter(GCollider* _Other)
{
	m_OverlapCount++;
	GetOwner()->OnCollisionEnter(_Other);
}

void GCollider::OnCollision(GCollider* _Other)
{
	GetOwner()->OnCollision(_Other);
}

void GCollider::OnCollisionExit(GCollider* _Other)
{
	GetOwner()->OnCollisionExit(_Other);
	m_OverlapCount--;
}

void GCollider::OnTriggerEnter(GCollider* _Other)
{
	m_OverlapCount++;
	GetOwner()->OnTriggerEnter(_Other);
}

void GCollider::OnTrigger(GCollider* _Other)
{
	GetOwner()->OnTrigger(_Other);
}

void GCollider::OnTriggerExit(GCollider* _Other)
{
	GetOwner()->OnTriggerExit(_Other);
	m_OverlapCount--;
}
