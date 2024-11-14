#include "pch.h"
#include "GHitBox.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"
#include "GFlipBookPlayer.h"

GHitBox::GHitBox() :
	GCreature(CREATURE_ID::HitBox),
	m_AttackType(ATTACK_TYPE::NONE),
	m_IsProjectile(false),
	m_SpriteRenderer(nullptr)
{
	DefaultStatsInfo* pStat = new DefaultStatsInfo;
	pStat->IsDead = true;

	SetStatInfo(pStat);

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();

	GetHitBox()->SetTrigger(true);
}

GHitBox::~GHitBox()
{
}

void GHitBox::Begin()
{
}

void GHitBox::Tick()
{
	GCreature::Tick();
}

void GHitBox::Render()
{
	m_SpriteRenderer->Render();
	m_FlipBookPlayer->Render();
}

void GHitBox::OnTriggerEnter(GCollider* _Collider)
{
	if (m_IsProjectile)
	{
		// 플레이어 레이어 일 때
		if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::MONSTER)
			DeleteGameObject(this);
		else if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::PLAYER)
			DeleteGameObject(this);
		else if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::OBJECT)
			DeleteGameObject(this);
	}

}