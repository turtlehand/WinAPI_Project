#include "pch.h"
#include "GCreature.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "GAssetManager.h"
#include "GRigidBody.h"
#include "GFSM.h"

#include "GBoxCollider.h"

#include "GFire.h"
#include "GHitBox.h";
#include "GFlipBookPlayer.h"

GCreature::GCreature(CREATURE_ID _CreatrueID) :
	m_CreatureID(_CreatrueID),
	m_StatInfo(nullptr),
	m_HitBox(nullptr),
	m_Element(nullptr),
	m_ElementTick(nullptr)
{
	

	//m_EffectAnim->SetDeleteColor(RGB(116, 116, 116));
}

GCreature::~GCreature()
{
	delete m_StatInfo;
	m_StatInfo = nullptr;
}

void GCreature::Awake()
{
	m_HitBox = AddComponent<GBoxCollider>();
}

void GCreature::Tick()
{
	StatusEffect();
	m_ElementTick = false;
}

void GCreature::OnTrigger(GCollider* _Collider)
{
	GCreature* Creature = dynamic_cast<GCreature*>(_Collider->GetOwner());
	if (Creature != nullptr)
	{
		Interaction_Element(Creature);
	}
}

void GCreature::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction_Attack(HitBox);
}

void GCreature::StatusEffect()
{
	if (m_StatInfo->Effect.ElementType == ELEMENT_TYPE::NONE)
		return;

	m_StatInfo->Effect.Duration -= DT;

	if (m_StatInfo->Effect.ElementType == ELEMENT_TYPE::FIRE)
	{
		Ignite();
	}

	if (m_StatInfo->Effect.Duration < 0)
	{
		IsValid(m_Element);
		m_StatInfo->Effect.Time = 0.f;
		m_StatInfo->Effect.Duration = 0.f;
		m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	}

}

void GCreature::Interaction_Element(GCreature* _Creature)
{
	// 무적 상태라면 무시
	if (m_StatInfo->IsInvincible)
		return;

	// 현재 틱에 속성 효과를 받았다면
	if (m_ElementTick)
		return;

	// 현재 소재가 속성 소재와 닿는다면
	MATERIAL_TYPE TMaterialType = m_StatInfo->Material;

	MATERIAL_TYPE CElementType = _Creature->GetStatInfo()->Material;

	// 소재 - 속성 반응
	if (TMaterialType == MATERIAL_TYPE::METAL && CElementType == MATERIAL_TYPE::LIGHTNING)
		Flow();
	else if ((TMaterialType == MATERIAL_TYPE::WOOD || TMaterialType == MATERIAL_TYPE::LIFE) &&
		CElementType == MATERIAL_TYPE::FIRE)
		Burn();
	else if (TMaterialType == MATERIAL_TYPE::LIFE && CElementType == MATERIAL_TYPE::LIGHTNING)
		Shock();
	else if (TMaterialType == MATERIAL_TYPE::LIFE && CElementType == MATERIAL_TYPE::ICE)
		Freeze();

	// 속성 - 속성 반응
	else if (TMaterialType == MATERIAL_TYPE::FIRE &&
		(CElementType == MATERIAL_TYPE::ICE || CElementType == MATERIAL_TYPE::WATER))
		Extinguish();
	else if (TMaterialType == MATERIAL_TYPE::WATER && CElementType == MATERIAL_TYPE::LIGHTNING)
		Flow();
	else if (TMaterialType == MATERIAL_TYPE::WATER && CElementType == MATERIAL_TYPE::ICE)
		Freeze();
	else if (TMaterialType == MATERIAL_TYPE::ICE && CElementType == MATERIAL_TYPE::FIRE)
		Melt();


	// 현재 상태이상에서 속성과 닿는다면

	ELEMENT_TYPE TElementType = m_StatInfo->Effect.ElementType;

	// 상태이상 속성 - 속성 반응
	if (TElementType == ELEMENT_TYPE::FIRE &&
		(CElementType == MATERIAL_TYPE::ICE || CElementType == MATERIAL_TYPE::WATER))
		Extinguish();
	else if (TElementType == ELEMENT_TYPE::WATER && CElementType == MATERIAL_TYPE::LIGHTNING)
		Flow();
	else if (TElementType == ELEMENT_TYPE::WATER && CElementType == MATERIAL_TYPE::ICE)
		Freeze();
	else if (TElementType == ELEMENT_TYPE::ICE && CElementType == MATERIAL_TYPE::FIRE)
		Melt();

	InteractionEffect_Element(_Creature);
}

void GCreature::Interaction_Attack(GHitBox* _HitBox)
{
	// 무적 상태라면 무시
	if (m_StatInfo->IsInvincible)
		return;

	// 현재 소재에 공격이 닿는다면

	ATTACK_TYPE HBAttackType = _HitBox->GetAttackType();

	MATERIAL_TYPE CMaterialType = m_StatInfo->Material;

	// 소재 - 공격 반응
	if (CMaterialType == MATERIAL_TYPE::STONE && HBAttackType == ATTACK_TYPE::STRIKE)
		Smash();
	else if (CMaterialType == MATERIAL_TYPE::LIFE && HBAttackType != ATTACK_TYPE::NONE )
		BeAttacked(_HitBox);
	else if (CMaterialType == MATERIAL_TYPE::WOOD && HBAttackType == ATTACK_TYPE::SLASH)
		CutWood();

	InteractionEffect_Attack(_HitBox);
}

void GCreature::Damaged(int _Damage)
{
	if ((int)CREATURE_ID::Item < (int)GetCreatureID())
		return;

	m_StatInfo->HP -= _Damage;

	if (m_StatInfo->HP <= 0)
		Dead();
}

void GCreature::Dead()
{
	if (m_StatInfo->IsDead)
		return;

	DropItem();
	m_StatInfo->IsDead = true;
	DeleteGameObject(this);
}

#pragma region Interaction

void GCreature::Smash()
{
	Damaged(2);
}

void GCreature::CutWood()
{

	Damaged(2);
}

void GCreature::BeAttacked(GHitBox* _HitBox)
{
	Damaged(_HitBox->GetDamage());
	KnockBack(_HitBox);

	// 피격 상태로 변경한다.
	GFSM* FSM = GetComponent<GFSM>();
	if (FSM == nullptr)
		return;

	FSM->ChanageState(L"BEATTACKED");
}

void GCreature::Burn()
{
	m_ElementTick = true;

	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::FIRE;
	m_StatInfo->Effect.Duration += 2 * DT;
}

void GCreature::Flow()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::LIGHTNING;
	m_StatInfo->Effect.Duration = 1.f;
}

void GCreature::Shock()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::LIGHTNING;
	m_StatInfo->Effect.Duration = 1.f;

	// 추가로 무기 떨구기
}

void GCreature::Freeze()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::ICE;
	m_StatInfo->Effect.Duration = 30.f;

}

void GCreature::Wet()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::WATER;
	m_StatInfo->Effect.Duration = 30.f;

}

void GCreature::Extinguish()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	m_StatInfo->Effect.Duration = 0.f;
}

void GCreature::Melt()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	m_StatInfo->Effect.Duration = 0.f;
}

#pragma endregion

void GCreature::KnockBack(GHitBox* _HitBox)
{

	GRigidBody* RigidBody = GetComponent<GRigidBody>();
	if (RigidBody == nullptr)
		return;

	Vec2 Direction = (_HitBox->GetGlobalPos() - this->GetGlobalPos()).Normalize();

	// x축 방향이 더 크다면
	if (fabs(Direction.x) > fabs(Direction.y))
	{
		// x 축 방향으로 이동한다.
		Direction = Vec2(Direction.x, 0.f);
	}
	else
	{
		// y 축 방향으로 이동한다.
		Direction = Vec2(0.f, Direction.y);
	}
	Direction = Direction.Normalize();

	RigidBody->AddForce(Direction * -35000);
}

void GCreature::Ignite()
{
	// 불이 나지 않았고 1초 이상 타고 있다면
	if (m_StatInfo->Effect.Duration >= 0.9f && !IsValid(m_Element))
	{
		//Damaged(1);
		m_StatInfo->Effect.Duration -= 1.f;

		// 불 효과 범위 추가
		// 상태이상 공격 박스
		m_Element = new GFire;
		CreateChildGameObject(this, m_Element, LAYER_TYPE::ELEMENT);

	}
	// 불에 1초 이상 타고 있다면
	else if (m_StatInfo->Effect.Duration > 1.f)
	{
		m_StatInfo->HP -= 1;

		if (m_StatInfo->HP <= 0)
			Dead();

		m_StatInfo->Effect.Duration -= 1.f;
		m_StatInfo->Effect.Time += 1.f;

	}
	else if (m_StatInfo->Effect.Time > 5.f && IsValid(m_Element))
	{
		DeleteGameObject(m_Element);
		m_Element = nullptr;
		m_StatInfo->Effect.Duration = 0.f;
		m_StatInfo->Effect.Time = 0.f;
	}
}

void GCreature::InstantIgnite()
{
	// 불이 나지 않았다면
	if (!IsValid(m_Element))
	{
		// 불 효과 범위 추가
		// 불 상태이상이 켜저도 Enter가 한번 발동 되므로 계속 불타지 않음
		// 상태이상 공격 박스
		m_Element = new GFire;
		CreateChildGameObject(this, m_Element, LAYER_TYPE::ELEMENT);

	}
}



