#include "pch.h"
#include "GCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "GCamera.h"

#include "GRigidBody.h"

GCollider::GCollider(COLLIDER_TYPE _Type) :
	GComponent(COMPONENT_TYPE::COLLIDER),
	m_Type(_Type),
	m_Offset(),
	m_Scale(),
	m_OverlapCount(0),
	m_Trigger(false)
{
}

GCollider::~GCollider()
{
	
}

void GCollider::FinalTick()
{
	// Collider 등록하기

	LAYER_TYPE LayerType = GetOwner()->GetLayerType();
	CLevelMgr::GetInst()->GetCurrentLevel()->RegisterCollider(this, LayerType);
}

void GCollider::EnterOverlap(GCollider* _Other)
{
	m_OverlapCount++;
	GetOwner()->EnterOverlap(_Other);
}

void GCollider::Overlap(GCollider* _Other)
{
	GetOwner()->Overlap(_Other);
}

void GCollider::ExitOverlap(GCollider* _Other)
{
	GetOwner()->ExitOverlap(_Other);
	m_OverlapCount--;
}
