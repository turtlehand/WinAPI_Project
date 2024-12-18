#include "pch.h"
#include "GPullRock.h"

#include "GBoxCollider.h"
#include "GRigidBody.h"
#include "GSpriteRenderer.h"
#include "GSound.h"

#include "GHitBox.h"

#include "GAssetManager.h"

GPullRock::GPullRock() :
	GCreature(CREATURE_ID::PullRock),
	m_RigidBody(nullptr),
	m_Sprite(nullptr)
{
	SetName(L"PullRock");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"PULL_ROCK", L"Sprite\\Object_16\\PULL_ROCK.sprite"));
}

GPullRock::~GPullRock()
{
}

void GPullRock::Awake()
{
	GCreature::Awake();

	// ���� ����
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::METAL;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	GetHitBox()->SetName(L"PullRock_HitBox");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));

	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(900.f);

	m_Sprite = AddComponent< GSpriteRenderer>();
	m_Sprite->SetSprite(GAssetManager::GetInst()->LoadSprite(L"PULL_ROCK", L"Sprite\\Object_16\\PULL_ROCK.sprite"));
	m_Sprite->SetScale(Vec2(4.f, 4.f));
}

/*
void GPullRock::Tick()
{
	GCreature::Tick();
}
*/

void GPullRock::Render()
{
	m_Sprite->Render();
}

void GPullRock::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction_Attack(HitBox);
}

