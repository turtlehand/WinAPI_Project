#include "pch.h"
#include "GHitBox.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"
#include "GFlipBookPlayer.h"

GHitBox::GHitBox() :
	m_AttackType(ATTACK_TYPE::NONE),
	m_MaterialType(MATERIAL_TYPE::NONE),
	m_Effect{},
	m_Damage(0),
	m_IsProjectile(false),
	m_Collider(nullptr),
	m_SpriteRenderer(nullptr)
{
	m_Collider = AddComponent<GBoxCollider>();
	m_Collider->SetTrigger(true);
	m_SpriteRenderer = AddComponent<GSpriteRenderer>();
	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();
}

GHitBox::~GHitBox()
{
}

void GHitBox::Begin()
{
}

void GHitBox::Tick()
{

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
	}

}

