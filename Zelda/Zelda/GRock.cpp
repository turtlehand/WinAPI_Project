#include "pch.h"
#include "GRock.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"

#include "GAssetManager.h"

GRock::GRock() :
	m_Sprite(nullptr)
{
	SetName(L"Rock");

	// ¹ÙÀ§ ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::STONE;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	GetHitBox()->SetName(L"Rock");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));

	m_Sprite = AddComponent< GSpriteRenderer>();
	m_Sprite->SetSprite(GAssetManager::GetInst()->LoadSprite(L"Rock", L"Sprite\\test_18.sprite"));
	m_Sprite->SetScale(Vec2(4.f, 4.f));
}

GRock::~GRock()
{
}

void GRock::Begin()
{
}

/*
void GRock::Tick()
{
	GCreature::Tick();
}
*/

void GRock::Render()
{
	m_Sprite->Render();
	RenderEffect();
}

void GRock::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if(HitBox != nullptr)
		Interaction(HitBox);
}



