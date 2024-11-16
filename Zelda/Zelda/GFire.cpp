#include "pch.h"
#include "GFire.h"

#include "GAssetManager.h"
#include "GBoxCollider.h"

GFire::GFire() :
	GHitBox(CREATURE_ID::Fire)
{
	SetName(L"Fire");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"FIRE_0", L"Sprite\\NPC_16\\FIRE_0.sprite"));
}

GFire::~GFire()
{
}

void GFire::Awake()
{
	GHitBox::Awake();
	GetHitBox()->SetScale(Vec2(96.f, 96.f));
	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"FIRE", L"FlipBook\\NPC_16\\FIRE.flip"));
	GetFlipBookPlayer()->SetPlay(0, 4, true);
	GetStatInfo()->Material = MATERIAL_TYPE::FIRE;
}


