#include "pch.h"
#include "GPullRock.h"

#include "GBoxCollider.h"
#include "GRigidBody.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"

#include "GAssetManager.h"

GPullRock::GPullRock() :
	m_Collider(nullptr),
	m_RigidBody(nullptr),
	m_Sprite(nullptr)
{
	SetName(L"PullRock");

	// ¹ÙÀ§ ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::METAL;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_Collider = AddComponent<GBoxCollider>();
	m_Collider->SetName(L"PullRock_HitBox");
	m_Collider->SetScale(Vec2(64.f, 64.f));

	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(900.f);

	m_Sprite = AddComponent< GSpriteRenderer>();
	m_Sprite->SetSprite(GAssetManager::GetInst()->LoadSprite(L"PULL_ROCK", L"Sprite\\Object_16\\PULL_ROCK.sprite"));
	m_Sprite->SetScale(Vec2(4.f, 4.f));
	m_Sprite->SetDeleteColor(RGB(116, 116, 116));
}

GPullRock::~GPullRock()
{
}

void GPullRock::Begin()
{
}

void GPullRock::Tick()
{
	GCreature::Tick();
}

void GPullRock::Render()
{
	m_Sprite->Render();
	RenderEffect();
}

void GPullRock::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction(HitBox);
}