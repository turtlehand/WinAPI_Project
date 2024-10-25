#include "pch.h"
#include "GCircleCollider.h"

GCircleCollider::GCircleCollider() :
	GCollider(COLLIDER_TYPE::CIRCLE),
	m_Radius(0.f)
{
}

GCircleCollider::~GCircleCollider()
{
}

void GCircleCollider::FinalTick()
{
	GCollider::FinalTick();
	Vec2 vPos = GetGlobalPos();

	if (GetCollision())
		DrawDebugCircle(PEN_TYPE::RED, 0.f, vPos, m_Radius);
	else
		DrawDebugCircle(PEN_TYPE::GREEN, 0.f, vPos, m_Radius);
}
