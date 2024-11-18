#include "pch.h"
#include "GFlint.h"

#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"


GFlint::GFlint() :
	GItem(CREATURE_ID::Flint),
	m_SpriteRenderer(nullptr),
	m_DeadTimer(0.f),
	m_TimerOn(false)
{
	SetName(L"Flint");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"FLINT", L"Sprite\\Item_16\\FLINT.sprite"));
}

GFlint::~GFlint()
{
}

void GFlint::InteractionEffect_Attack(GHitBox* _HitBox)
{
	if (_HitBox->GetMaterialType() == MATERIAL_TYPE::STONE ||
		_HitBox->GetMaterialType() == MATERIAL_TYPE::METAL)
	{
		InstantIgnite();
		m_DeadTimer = 0.5f;
		m_TimerOn = true;
	}
}

void GFlint::Awake()
{
	GItem::Awake();

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
	m_SpriteRenderer->SetScale(Vec2(2.f, 2.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetName(L"FIREWOOD_HITBOX");
	GetHitBox()->SetScale(Vec2(32.f, 32.f));
	GetHitBox()->SetTrigger(true);

}

void GFlint::Tick()
{
	if (m_TimerOn)
	{
		m_DeadTimer -= DT;
		if (m_DeadTimer < 0.f)
			DeleteGameObject(this);
	}
}

void GFlint::Render()
{
	m_SpriteRenderer->Render();
}