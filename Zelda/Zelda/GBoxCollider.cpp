#include "pch.h"
#include "GBoxCollider.h"

GBoxCollider::GBoxCollider() :
	GCollider(COLLIDER_TYPE::RECTANGLE)
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
	if (GetOverlapCount())
		DrawDebugRect(PEN_TYPE::RED, 0.f, vPos, vScale);
	else
		DrawDebugRect(PEN_TYPE::GREEN, 0.f, vPos, vScale);
}
