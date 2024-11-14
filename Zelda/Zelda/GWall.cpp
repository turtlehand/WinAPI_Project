#include "pch.h"
#include "GWall.h"

#include "GBoxCollider.h"

GWall::GWall()
{
	SetName(L"Wall");

	GBoxCollider* Collider = AddComponent<GBoxCollider>();
	Collider->SetScale(Vec2(64.f, 64.f));
	Collider->SetTrigger(false);
}

GWall::~GWall()
{
}
