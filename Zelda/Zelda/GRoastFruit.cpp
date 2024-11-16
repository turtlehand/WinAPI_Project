#include "pch.h"
#include "GRoastFruit.h"

#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"

GRoastFruit::GRoastFruit() :
	GItem(CREATURE_ID::Roast_Fruit),
	m_SpriteRenderer(nullptr)
{
	SetName(L"Roast_Fruit");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"ROAST_FRUIT", L"Sprite\\Item_16\\ROAST_FRUIT.sprite"));
}

GRoastFruit::~GRoastFruit()
{

}

void GRoastFruit::Awake()
{
	GItem::Awake();

	// 구운 열매 스탯
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetSprite(GAssetManager::GetInst()->LoadSprite(L"ROAST_FRUIT", L"Sprite\\Item_16\\ROAST_FRUIT.sprite"));
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetName(L"FRUIT_HITBOX");
	GetHitBox()->SetScale(Vec2(32.f, 32.f));
	GetHitBox()->SetTrigger(true);
}

void GRoastFruit::Render()
{
	m_SpriteRenderer->Render();
}

void GRoastFruit::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction_Attack(HitBox);
}

void GRoastFruit::UseItem(GCreature* _User)
{
	_User->GetStatInfo()->HP += 12;
}

void GRoastFruit::DropItem()
{

}