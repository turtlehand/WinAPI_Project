#include "pch.h"
#include "GFire.h"

#include "GAssetManager.h"
#include "GBoxCollider.h"

GFire::GFire() :
	GHitBox(CREATURE_ID::Fire)
{
	SetName(L"Fire");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"FIRE", L"FlipBook\\NPC_16\\FIRE.flip"));
	GetFlipBookPlayer()->SetPlay(0, 4, true);
	GetStatInfo()->Material = MATERIAL_TYPE::FIRE;
}

GFire::~GFire()
{
}
