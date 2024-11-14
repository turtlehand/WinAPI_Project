#include "pch.h"
#include "GArrow.h"

#include "GRigidBody.h"

#include "GAssetManager.h"
#include "GSpriteRenderer.h"

#include "GBoxCollider.h"

GArrow::GArrow() :
	m_RigidBody(nullptr)
{
	m_RigidBody = AddComponent<GRigidBody>();
	
	SetAttackType(ATTACK_TYPE::THRUSHT);
	SetMaterialType(MATERIAL_TYPE::WOOD);
	SetIsProjectile(true);

	GetSpriteRenderer()->SetScale(Vec2(4.f, 4.f));
	GetSpriteRenderer()->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetTrigger(true);
}

GArrow::~GArrow()
{
}

void GArrow::Begin()
{
	GHitBox::Begin();
}

void GArrow::Tick()
{
	GHitBox::Tick();
	m_RigidBody->SetVelocity(m_Velocity);
}


void GArrow::Render()
{
	GHitBox::Render();
}

void GArrow::InteractionEffect_Element(GCreature* _Creature)
{
	if (_Creature->GetStatInfo()->Material == MATERIAL_TYPE::FIRE)
	{
		InstantIgnite();
	}
}

void GArrow::SetVelocity(Vec2 _Velocity)
{
	if (_Velocity.Normalize() == Vec2::up())
	{
		GetSpriteRenderer()->SetSprite(GAssetManager::GetInst()->LoadSprite(L"ARROW_Y", L"Sprite\\Item_16\\ARROW_Y.sprite"));
		GetHitBox()->SetScale(Vec2(32.f, 64.f));
	}
	else if (_Velocity.Normalize() == Vec2::down())
	{
		GetSpriteRenderer()->SetSprite(GAssetManager::GetInst()->LoadSprite(L"ARROW_Y", L"Sprite\\Item_16\\ARROW_Y.sprite"));
		GetSpriteRenderer()->SetYFlip(true);

		GetHitBox()->SetScale(Vec2(32.f, 64.f));
	}
	else if (_Velocity.Normalize() == Vec2::left())
	{
		GetSpriteRenderer()->SetSprite(GAssetManager::GetInst()->LoadSprite(L"ARROW_X", L"Sprite\\Item_16\\ARROW_X.sprite"));
		GetSpriteRenderer()->SetXFlip(true);

		GetHitBox()->SetScale(Vec2(64.f, 32.f));
	}
	else if (_Velocity.Normalize() == Vec2::right())
	{
		GetSpriteRenderer()->SetSprite(GAssetManager::GetInst()->LoadSprite(L"ARROW_X", L"Sprite\\Item_16\\ARROW_X.sprite"));

		GetHitBox()->SetScale(Vec2(64.f, 32.f));
	}
		

	m_Velocity = _Velocity;
		
}

