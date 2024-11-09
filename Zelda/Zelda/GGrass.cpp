#include "pch.h"
#include "GGrass.h"

#include "GBoxCollider.h"
#include "GFlipBookPlayer.h"

#include "GHitBox.h"
#include "GLog.h"

#include "GAssetManager.h"

GGrass::GGrass() :
	m_Collider(nullptr),
	m_FlipBookPlayer(nullptr)
{
	SetName(L"Grass");

	// Ç® ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::METAL;
	pInfo->MaxHP = 1;
	pInfo->HP = 1;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_Collider = AddComponent< GBoxCollider>();
	m_Collider->SetName(L"Grass_HitBox");
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->SetTrigger(true);

	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"GRASS", L"FlipBook\\OBJECT_16\\GRASS.flip"));
	m_FlipBookPlayer->SetPlay(0, 5, true);
	m_FlipBookPlayer->Pause();
}

GGrass::~GGrass()
{
}

void GGrass::InteractionEffect()
{
	m_FlipBookPlayer->SetPlay(0, 10, false);
}

void GGrass::Begin()
{
}

void GGrass::Tick()
{
	GCreature::Tick();
}

void GGrass::Render()
{
	m_FlipBookPlayer->Render();
	RenderEffect();
}

void GGrass::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction(HitBox);
}