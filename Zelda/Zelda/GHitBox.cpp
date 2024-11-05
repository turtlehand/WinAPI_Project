#include "pch.h"
#include "GHitBox.h"

#include "GBoxCollider.h"

GHitBox::GHitBox() :
	m_AttackType(ATTACK_TYPE::NONE),
	m_MaterialType(MATERIAL_TYPE::NONE),
	m_Damage(0),
	m_IsProjectile(false),
	m_Collider(nullptr)
{
}

GHitBox::~GHitBox()
{
}

void GHitBox::Awake()
{
	m_Collider = AddComponent<GBoxCollider>();
}

void GHitBox::Begin()
{
}

void GHitBox::Tick()
{
}

void GHitBox::Render()
{
}

void GHitBox::OnEnable()
{

}

void GHitBox::OnDisable()
{
	
}

void GHitBox::EnterOverlap(GCollider* _Collider)
{
}

