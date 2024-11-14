#include "pch.h"
#include "GFlint.h"

#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"


GFlint::GFlint() :
	GItem(CREATURE_ID::Flint),
	m_SpriteRenderer(nullptr)
{
	SetName(L"Flint");

	// ÀåÀÛ ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::STONE;
	pInfo->MaxHP = 100;
	pInfo->HP = 100;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetSprite(GAssetManager::GetInst()->LoadSprite(L"FLINT", L"Sprite\\Item_16\\FLINT.sprite"));
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetName(L"FIREWOOD_HITBOX");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetHitBox()->SetTrigger(true);

	SetItemImage(m_SpriteRenderer->GetSprite());
}

GFlint::~GFlint()
{
}

void GFlint::InteractionEffect_Element(GCreature* _Creature)
{
	MATERIAL_TYPE CElementType = _Creature->GetStatInfo()->Material;

	if ( CElementType == MATERIAL_TYPE::FIRE )
		Burn();
}

void GFlint::InteractionEffect_Attack(GHitBox* _HitBox)
{
	if (_HitBox->GetMaterialType() == MATERIAL_TYPE::STONE ||
		_HitBox->GetMaterialType() == MATERIAL_TYPE::METAL)
	{
		GetStatInfo()->HP = 1;
		InstantIgnite();
	}
}

void GFlint::Begin()
{
}

void GFlint::Render()
{
	m_SpriteRenderer->Render();
}