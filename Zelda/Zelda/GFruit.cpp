#include "pch.h"
#include "GFruit.h"

#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"

GFruit::GFruit() :
	GItem(ITEM_ID::Flint),
	m_SpriteRenderer(nullptr)
{
	SetName(L"Fruit");

	// ¿­¸Å ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::STONE;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetSprite(GAssetManager::GetInst()->LoadSprite(L"FLINT", L"Sprite\\Item_16\\FLINT.sprite"));
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetName(L"FRUIT_HITBOX");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetHitBox()->SetTrigger(true);
}

GFruit::~GFruit()
{

}

void GFruit::Begin()
{
}

void GFruit::Render()
{
	m_SpriteRenderer->Render();
	GCreature::RenderEffect();
}

void GFruit::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction(HitBox);
}

void GFruit::UseItem()
{

}

void GFruit::DropItem()
{

}