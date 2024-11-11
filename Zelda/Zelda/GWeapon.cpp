#include "pch.h"
#include "GWeapon.h"

#include "GPlayer.h"
#include "GMonster.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"
#include "GAssetManager.h"

GWeapon::GWeapon(ITEM_ID _WeaponID) : 
	GItem(_WeaponID),
	m_SpriteRenderer(nullptr),
	m_SpriteX(nullptr),
	m_SpriteY(nullptr)
{
	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_SpriteRenderer->SetScale(Vec2(4.f, 4.f));
	m_SpriteRenderer->SetDeleteColor(RGB(116, 116, 116));

	// 300�� 400 ���̰� �ƴ϶�� ���� ó��
	assert(300 < (int)GetItemID() && (int)GetItemID() < 400);

	WeaponInfo* pInfo = new WeaponInfo;
	pInfo->MaxHP = 100;
	pInfo->HP = 100;
	pInfo->Speed = 0;
	pInfo->IsDead = false;

	switch (GetItemID())
	{
		case ITEM_ID::Wooden_Sword:
		{
			pInfo->Material = MATERIAL_TYPE::WOOD;
			pInfo->AttackPower = 2;
			pInfo->AttackType = ATTACK_TYPE::SLASH;
			m_SpriteX = GAssetManager::GetInst()->LoadSprite(L"WOODEN_SWORD_X", L"Sprite\\Item_16\\Weapon\\WOODEN_SWORD_X.sprite");
			m_SpriteY = GAssetManager::GetInst()->LoadSprite(L"WOODEN_SWORD_Y", L"Sprite\\Item_16\\Weapon\\WOODEN_SWORD_Y.sprite");
			m_SpriteRenderer->SetSprite(m_SpriteX);
		}
		break;
		case ITEM_ID::Iron_Sword:
		{
			pInfo->Material = MATERIAL_TYPE::METAL;
			pInfo->AttackPower = 4;
			pInfo->AttackType = ATTACK_TYPE::SLASH;
			m_SpriteX = GAssetManager::GetInst()->LoadSprite(L"METAL_SWORD_X", L"Sprite\\Item_16\\Weapon\\METAL_SWORD_X.sprite");
			m_SpriteY = GAssetManager::GetInst()->LoadSprite(L"METAL_SWORD_Y", L"Sprite\\Item_16\\Weapon\\METAL_SWORD_Y.sprite");
			m_SpriteRenderer->SetSprite(m_SpriteX);
		}
		break;
		case ITEM_ID::Stone_Hammer:
		{
			pInfo->Material = MATERIAL_TYPE::STONE;
			pInfo->AttackPower = 4;
			pInfo->AttackType = ATTACK_TYPE::STRIKE;
		}
		break;
		case ITEM_ID::Iron_Hammer:
		{
			pInfo->Material = MATERIAL_TYPE::METAL;
			pInfo->AttackPower = 6;
			pInfo->AttackType = ATTACK_TYPE::STRIKE;
		}
		break;
		case ITEM_ID::Wooden_Spear:
		{
			pInfo->Material = MATERIAL_TYPE::WOOD;
			pInfo->AttackPower = 1;
			pInfo->AttackType = ATTACK_TYPE::THRUSHT;
		}
		break;
		case ITEM_ID::Iron_Spear:
		{
			pInfo->Material = MATERIAL_TYPE::METAL;
			pInfo->AttackPower = 3;
			pInfo->AttackType = ATTACK_TYPE::THRUSHT;
		}
		break;
		case ITEM_ID::Korok_Leaf:
		{
			pInfo->Material = MATERIAL_TYPE::WOOD;
			pInfo->AttackPower = 1;
			pInfo->AttackType = ATTACK_TYPE::STRIKE;
		}
		break;
	}

	SetStatInfo(pInfo);

	GetHitBox()->SetName(L"Weapon_HITBOX");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetHitBox()->SetTrigger(true);

	SetItemImage(m_SpriteRenderer->GetSprite());
}

GWeapon::~GWeapon()
{
}

void GWeapon::Begin()
{
}

void GWeapon::Render()
{
	m_SpriteRenderer->Render();
	GCreature::RenderEffect();
}

void GWeapon::UseItem(GCreature* _User)
{
	// ������ ����
	if (_User->GetLayerType() == LAYER_TYPE::PLAYER)
	{
		GPlayer* pPlayer = dynamic_cast<GPlayer*>(_User);
		assert(pPlayer != nullptr);
		pPlayer->SetAttackBox(GetItemID(), GetWeaponInfo(), m_SpriteX, m_SpriteY);
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

