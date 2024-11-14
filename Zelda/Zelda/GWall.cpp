#include "pch.h"
#include "GWall.h"

#include "GBoxCollider.h"

void GWall::Awake()
{
	GBoxCollider* Collider = AddComponent<GBoxCollider>();
	Collider->SetScale(Vec2(64.f, 64.f));
	Collider->SetTrigger(false);
}

GWall::GWall()
{
	SetName(L"Wall");
}

GWall::~GWall()
{
}
