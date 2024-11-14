#include "pch.h"
#include "GGrass.h"

#include "GBoxCollider.h"
#include "GFlipBookPlayer.h"

#include "GHitBox.h"
#include "GLog.h"

#include "GAssetManager.h"

GGrass::GGrass() :
	GCreature(CREATURE_ID::Grass),
	m_FlipBookPlayer(nullptr)
{
	SetName(L"Grass");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"GRASS_0", L"Sprite\\Object_16\\GRASS_0.sprite"));

}

GGrass::~GGrass()
{
}


void GGrass::Awake()
{
	GCreature::Awake();

	// Ç® ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 1;
	pInfo->HP = 1;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	GetHitBox()->SetName(L"Grass_HitBox");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));
	GetHitBox()->SetTrigger(true);

	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"GRASS", L"FlipBook\\OBJECT_16\\GRASS.flip"));
	m_FlipBookPlayer->SetPlay(0, 5, false);
}

/*
void GGrass::Tick()
{
	GCreature::Tick();
}
*/

void GGrass::Render()
{
	m_FlipBookPlayer->Render();
}

void GGrass::OnTriggerEnter(GCollider* _Collider)
{
	GCreature::OnTriggerEnter(_Collider);

	if (m_FlipBookPlayer->IsFinish())
	{
		GCreature* Creature = dynamic_cast<GCreature*>(_Collider->GetOwner());
		if (Creature != nullptr)
			m_FlipBookPlayer->SetPlay(0, 10, false);
	}
	
}
