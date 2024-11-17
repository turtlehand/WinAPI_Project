#include "pch.h"
#include "GArrow.h"

#include "GRigidBody.h"

#include "GAssetManager.h"
#include "GSpriteRenderer.h"

#include "GBoxCollider.h"

GArrow::GArrow() :
	m_RigidBody(nullptr)
{

}

GArrow::~GArrow()
{
}

void GArrow::Awake()
{
	GHitBox::Awake();
	m_RigidBody = AddComponent<GRigidBody>();

	SetAttackType(ATTACK_TYPE::THRUSHT);
	SetMaterialType(MATERIAL_TYPE::WOOD);
	SetIsProjectile(true);

	GetSpriteRenderer()->SetScale(Vec2(4.f, 4.f));
	GetSpriteRenderer()->SetDeleteColor(RGB(116, 116, 116));

	GetHitBox()->SetTrigger(true);
	
}

void GArrow::Begin()
{
	GHitBox::Begin();
	DeleteGameObject(this, 5.f);
}

void GArrow::Tick()
{
	GHitBox::Tick();
	m_RigidBody->SetVelocity(m_Velocity);

	if (isnan(GetPos().x) || isnan(GetPos().y))
		bool isnan = true;
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

	// 불타고 있을 때 나무에 닿는다며 대상은 불이 붙는다.
	if (GetElement() != nullptr && _Creature->GetStatInfo()->Material == MATERIAL_TYPE::WOOD)
	{
		_Creature->InstantIgnite();
	}
}

void GArrow::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox::OnTriggerEnter(_Collider);

	GHitBox* Element = dynamic_cast<GHitBox*>(GetElement());

	if (Element == nullptr)
		return;

	// 불화살 일 때
	if (Element->GetStatInfo()->Material == MATERIAL_TYPE::FIRE)
	{
		// 대상이 크리쳐인지 확인
		GCreature* Creature = dynamic_cast<GCreature*>(_Collider->GetOwner());

		// 대상이 나무, 생명체라면 즉시 불을 붙인다.
		if (Creature->GetStatInfo()->Material == MATERIAL_TYPE::WOOD || Creature->GetStatInfo()->Material == MATERIAL_TYPE::LIFE)
		{
			Creature->InstantIgnite();
		}
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

