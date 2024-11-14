#include "pch.h"
#include "GWeapon.h"

#include "GPlayer.h"
#include "GMonster.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"
#include "GAssetManager.h"

GWeapon::GWeapon(CREATURE_ID _CreatureID) :
	GItem(_CreatureID),
	m_SpriteRenderer(nullptr),
	m_SpriteX(nullptr),
	m_SpriteY(nullptr)
{
	SetName(L"Weapon");
	// 300과 400 사이가 아니라면 오류 처리
	assert((int)CREATURE_ID::WEAPON < (int)GetCreatureID() && (int)GetCreatureID() < (int)CREATURE_ID::TOOLS);

	WeaponInfo* pInfo = new WeaponInfo;
	pInfo->MaxHP = 100;
	pInfo->HP = 100;
	pInfo->Speed = 0;
	pInfo->IsDead = false;

	switch (GetCreatureID())
	{
	case CREATURE_ID::Wooden_Sword:
	{
		pInfo->Material = MATERIAL_TYPE::WOOD;
		pInfo->AttackPower = 1;
		pInfo->AttackType = ATTACK_TYPE::SLASH;
		m_SpriteX = GAssetManager::GetInst()->LoadSprite(L"WOODEN_SWORD_X", L"Sprite\\Item_16\\Weapon\\WOODEN_SWORD_X.sprite");
		m_SpriteY = GAssetManager::GetInst()->LoadSprite(L"WOODEN_SWORD_Y", L"Sprite\\Item_16\\Weapon\\WOODEN_SWORD_Y.sprite");
	}
	break;
	case CREATURE_ID::Iron_Sword:
	{
		pInfo->Material = MATERIAL_TYPE::METAL;
		pInfo->AttackPower = 3;
		pInfo->AttackType = ATTACK_TYPE::SLASH;
		m_SpriteX = GAssetManager::GetInst()->LoadSprite(L"METAL_SWORD_X", L"Sprite\\Item_16\\Weapon\\METAL_SWORD_X.sprite");
		m_SpriteY = GAssetManager::GetInst()->LoadSprite(L"METAL_SWORD_Y", L"Sprite\\Item_16\\Weapon\\METAL_SWORD_Y.sprite");
	}
	break;
	case CREATURE_ID::Stone_Hammer:
	{
		pInfo->Material = MATERIAL_TYPE::STONE;
		pInfo->AttackPower = 1;
		pInfo->AttackType = ATTACK_TYPE::STRIKE;
	}
	break;
	case CREATURE_ID::Iron_Hammer:
	{
		pInfo->Material = MATERIAL_TYPE::METAL;
		pInfo->AttackPower = 3;
		pInfo->AttackType = ATTACK_TYPE::STRIKE;
	}
	break;
	case CREATURE_ID::Wooden_Spear:
	{
		pInfo->Material = MATERIAL_TYPE::WOOD;
		pInfo->AttackPower = 2;
		pInfo->AttackType = ATTACK_TYPE::THRUSHT;
	}
	break;
	case CREATURE_ID::Iron_Spear:
	{
		pInfo->Material = MATERIAL_TYPE::METAL;
		pInfo->AttackPower = 4;
		pInfo->AttackType = ATTACK_TYPE::THRUSHT;
	}
	break;
	case CREATURE_ID::Korok_Leaf:
	{
		pInfo->Material = MATERIAL_TYPE::WOOD;
		pInfo->AttackPower = 1;
		pInfo->AttackType = ATTACK_TYPE::STRIKE;
	}
	break;
	}

	SetStatInfo(pInfo);
}

GWeapon::~GWeapon()
{
	
}

void GWeapon::Awake()
{
	GItem::Awake();

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	m_SpriteRenderer->SetSprite(m_SpriteX);

	GetHitBox()->SetName(L"Weapon_HITBOX");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetHitBox()->SetTrigger(true);

	SetItemImage(m_SpriteRenderer->GetSprite());
}

void GWeapon::Render()
{
	m_SpriteRenderer->Render();
}

void GWeapon::UseItem(GCreature* _User)
{
	// 아이템 장착
	if (_User->GetLayerType() == LAYER_TYPE::PLAYER)
	{
		GPlayer* pPlayer = dynamic_cast<GPlayer*>(_User);
		assert(pPlayer != nullptr);
		pPlayer->SetAttackBox(GetCreatureID(), GetWeaponInfo(), m_SpriteX, m_SpriteY);
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

void GWeapon::SpecialEffect()
{
}


