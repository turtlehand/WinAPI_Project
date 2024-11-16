#include "pch.h"
#include "GFruit.h"

#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"
#include "GRoastFruit.h"

GFruit::GFruit() :
	GItem(CREATURE_ID::Fruit),
	m_SpriteRenderer(nullptr)
{
	SetName(L"Fruit");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"FRUIT", L"Sprite\\Item_16\\FRUIT.sprite"));
}

GFruit::~GFruit()
{

}

void GFruit::Awake()
{
	GItem::Awake();

	// 열매 스탯
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetSprite(GAssetManager::GetInst()->LoadSprite(L"FRUIT", L"Sprite\\Item_16\\FRUIT.sprite"));
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetName(L"FRUIT_HITBOX");
	GetHitBox()->SetScale(Vec2(32.f, 32.f));
	GetHitBox()->SetTrigger(true);

}

void GFruit::Render()
{
	m_SpriteRenderer->Render();
}

void GFruit::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction_Attack(HitBox);
}

void GFruit::UseItem(GCreature* _User)
{
	_User->GetStatInfo()->HP += 4;
}

void GFruit::DropItem()
{
	// 불에 타고 있다면 익은 열매를 떨군다.
	if (GetStatInfo()->Effect.ElementType != ELEMENT_TYPE::FIRE)
		return;

	CObj* DropRoastFruit = new GRoastFruit;
	DropRoastFruit->SetPos(GetPos().x, GetPos().y);
	CreateGameObject(DropRoastFruit, LAYER_TYPE::ITEM);
}