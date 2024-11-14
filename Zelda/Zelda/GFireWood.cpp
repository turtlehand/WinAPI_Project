#include "pch.h"
#include "GFireWood.h"

#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"

GFireWood::GFireWood() :
	GItem(CREATURE_ID::Fire_Wood),
	m_SpriteRenderer(nullptr)
{
	SetName(L"FireWood");

	// ÀåÀÛ ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 100;
	pInfo->HP = 100;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetSprite(GAssetManager::GetInst()->LoadSprite(L"FIRE_WOOD",L"Sprite\\Item_16\\FIRE_WOOD.sprite"));
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetName(L"FIREWOOD_HITBOX");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetHitBox()->SetTrigger(true);

	SetItemImage(m_SpriteRenderer->GetSprite());
}

GFireWood::~GFireWood()
{
}

void GFireWood::Begin()
{
}

void GFireWood::Tick()
{
	GCreature::Tick();
	if (GetStatInfo()->Effect.ElementType == ELEMENT_TYPE::FIRE)
	{
		InstantIgnite();
	}

	GetStatInfo()->Effect.Duration = 0.f;
}

void GFireWood::Render()
{
	m_SpriteRenderer->Render();
}
