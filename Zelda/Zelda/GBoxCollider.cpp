#include "pch.h"
#include "GBoxCollider.h"

GBoxCollider::GBoxCollider(COLLIDER_TYPE _ColliderType) :
	GCollider(_ColliderType),
	m_Scale(1.f, 1.f)
{
}

GBoxCollider::~GBoxCollider()
{

}

void GBoxCollider::FinalTick()
{
	GCollider::FinalTick();
	Vec2 vPos = GetGlobalPos();
	Vec2 vScale = GetScale();
	if (GetCollision())
		DrawDebugRect(PEN_TYPE::RED, 0.f, vPos, vScale);
	else
		DrawDebugRect(PEN_TYPE::GREEN, 0.f, vPos, vScale);
}
