#include "pch.h"
#include "GHitBox.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"
#include "GFlipBookPlayer.h"

GHitBox::GHitBox(CREATURE_ID _CreatureID) :
	GCreature(CREATURE_ID::HitBox),
	m_AttackType(ATTACK_TYPE::NONE),
	m_IsProjectile(false),
	m_SpriteRenderer(nullptr),
	m_FlipBookPlayer(nullptr)
{

}

GHitBox::~GHitBox()
{

}

void GHitBox::Awake()
{
	GCreature::Awake();

	DefaultStatsInfo* pStat = GetStatInfo();
	if (pStat == nullptr)
	{
		pStat = new DefaultStatsInfo;
		pStat->IsDead = true;
		SetStatInfo(pStat);
	}
	

	

	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();

	GetHitBox()->SetTrigger(true);
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
		{
			GCreature* Creature = dynamic_cast<GCreature*>(_Collider->GetOwner());
			assert(Creature != nullptr);
			if(Creature->GetCreatureID() != CREATURE_ID::Grass)
    				DeleteGameObject(this);
		}
		else if(_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::WALL)
			DeleteGameObject(this);
	}

}