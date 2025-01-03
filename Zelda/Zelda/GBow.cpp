#include "pch.h"
#include "GBow.h"

#include "GAssetManager.h"
#include "GSound.h"

#include "GSpriteRenderer.h"
#include "GBoxCollider.h"

#include "GPlayer.h"

GBow::GBow() :
	GItem(CREATURE_ID::Bow),
	m_SpriteRenderer(nullptr)
{
	SetName(L"Bow");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"BOW", L"Sprite\\Item_16\\BOW_Y.sprite"));
	
}

GBow::~GBow()
{
}

void GBow::Awake()
{
	GItem::Awake();

	// ���� ����
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 4;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetSprite(GAssetManager::GetInst()->LoadSprite(L"BOW", L"Sprite\\Item_16\\BOW_Y.sprite"));
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetName(L"BOW_HITBOX");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetHitBox()->SetTrigger(true);
}

void GBow::Render()
{
	m_SpriteRenderer->Render();
}

void GBow::UseItem(GCreature* _User)
{
	// ������ ����
	if (_User->GetLayerType() == LAYER_TYPE::PLAYER)
	{
		GPlayer* pPlayer = dynamic_cast<GPlayer*>(_User);
		assert(pPlayer != nullptr);
		pPlayer->SetTool(GetCreatureID());
		GAssetManager::GetInst()->LoadSound(L"Equip", L"Sound\\Sound_Effects\\LOZ_Get_Rupee.wav")->Play();
	}
	/*
	else if (_User->GetLayerType() == LAYER_TYPE::MONSTER)
	{
		GMonster* pMonster = dynamic_cast<GMonster*>(_User);
		assert(pMonster != nullptr);
		pMonster->SetAttackBox(GetWeaponInfo());
	}
	*/
	else
	{
		assert(false);
	}
}


