#include "pch.h"
#include "Collider.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "GCamera.h"

#include "GRigidBody.h"

Collider::Collider() :
	Component(COMPONENT_TYPE::COLLIDER),
	m_Offset(),
	m_Scale(),
	m_Active(true),
	m_OverlapCount(0),
	m_Trigger(false)
{
}

Collider::~Collider()
{
	
}

void Collider::FinalTick()
{
	// Collider 등록하기

	LAYER_TYPE LayerType = GetOwner()->GetLayerType();
	CLevelMgr::GetInst()->GetCurrentLevel()->RegisterCollider(this, LayerType);
	Vec2 vPos = GetGlobalPos();

	if (m_OverlapCount)
		DrawDebugRect(PEN_TYPE::RED, 0.f, vPos, m_Scale );
	else
		DrawDebugRect(PEN_TYPE::GREEN, 0.f, vPos, m_Scale);
}

void Collider::EnterOverlap(Collider* _Other)
{
	m_OverlapCount++;
	GetOwner()->EnterOverlap(_Other);
}

void Collider::Overlap(Collider* _Other)
{
	GetOwner()->Overlap(_Other);
}

void Collider::ExitOverlap(Collider* _Other)
{
	GetOwner()->ExitOverlap(_Other);
	m_OverlapCount--;
}
