#include "pch.h"
#include "GFireWood.h"

#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"

GFireWood::GFireWood() :
	GItem(ITEM_ID::Fire_Wood),
	m_SpriteRenderer(nullptr)
{
	SetName(L"FireWood");

	// 장작 스탯
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
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
}

GFireWood::~GFireWood()
{
}

void GFireWood::BurnStatusEffect()
{
	// 불에 의한 피해를 입지 않으며 지속시간이 10배가 된다.
	if (GetStatInfo()->Effect.Duration - GetStatInfo()->Effect.Time >= 1)
	{
		GetStatInfo()->Effect.Time += DT / 2;
	}
}

void GFireWood::Begin()
{
}

void GFireWood::Render()
{
	m_SpriteRenderer->Render();
	GCreature::RenderEffect();
}

void GFireWood::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction(HitBox);
}