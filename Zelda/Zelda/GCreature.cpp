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
	// ���� ���¶�� ����
	if (m_StatInfo->IsInvincible)
		return;

	// ���� ƽ�� �Ӽ� ȿ���� �޾Ҵٸ�
	if (m_ElementTick)
		return;

	// ���� ���簡 �Ӽ� ����� ��´ٸ�
	MATERIAL_TYPE TMaterialType = m_StatInfo->Material;

	MATERIAL_TYPE CElementType = _Creature->GetStatInfo()->Material;

	// ���� - �Ӽ� ����
	if (TMaterialType == MATERIAL_TYPE::METAL && CElementType == MATERIAL_TYPE::LIGHTNING)
		Flow();
	else if ((TMaterialType == MATERIAL_TYPE::WOOD || TMaterialType == MATERIAL_TYPE::LIFE) &&
		CElementType == MATERIAL_TYPE::FIRE)
		Burn();
	else if (TMaterialType == MATERIAL_TYPE::LIFE && CElementType == MATERIAL_TYPE::LIGHTNING)
		Shock();
	else if (TMaterialType == MATERIAL_TYPE::LIFE && CElementType == MATERIAL_TYPE::ICE)
		Freeze();

	// �Ӽ� - �Ӽ� ����
	else if (TMaterialType == MATERIAL_TYPE::FIRE &&
		(CElementType == MATERIAL_TYPE::ICE || CElementType == MATERIAL_TYPE::WATER))
		Extinguish();
	else if (TMaterialType == MATERIAL_TYPE::WATER && CElementType == MATERIAL_TYPE::LIGHTNING)
		Flow();
	else if (TMaterialType == MATERIAL_TYPE::WATER && CElementType == MATERIAL_TYPE::ICE)
		Freeze();
	else if (TMaterialType == MATERIAL_TYPE::ICE && CElementType == MATERIAL_TYPE::FIRE)
		Melt();


	// ���� �����̻󿡼� �Ӽ��� ��´ٸ�

	ELEMENT_TYPE TElementType = m_StatInfo->Effect.ElementType;

	// �����̻� �Ӽ� - �Ӽ� ����
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
	// ���� ���¶�� ����
	if (m_StatInfo->IsInvincible)
		return;

	// ���� ���翡 ������ ��´ٸ�

	ATTACK_TYPE HBAttackType = _HitBox->GetAttackType();

	MATERIAL_TYPE CMaterialType = m_StatInfo->Material;

	// ���� - ���� ����
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

	// �ǰ� ���·� �����Ѵ�.
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

	// �߰��� ���� ������
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

	// x�� ������ �� ũ�ٸ�
	if (fabs(Direction.x) > fabs(Direction.y))
	{
		// x �� �������� �̵��Ѵ�.
		Direction = Vec2(Direction.x, 0.f);
	}
	else
	{
		// y �� �������� �̵��Ѵ�.
		Direction = Vec2(0.f, Direction.y);
	}
	Direction = Direction.Normalize();

	RigidBody->AddForce(Direction * -35000);
}

void GCreature::Ignite()
{
	// ���� ���� �ʾҰ� 1�� �̻� Ÿ�� �ִٸ�
	if (m_StatInfo->Effect.Duration >= 0.9f && !IsValid(m_Element))
	{
		//Damaged(1);
		m_StatInfo->Effect.Duration -= 1.f;

		// �� ȿ�� ���� �߰�
		// �����̻� ���� �ڽ�
		m_Element = new GFire;
		CreateChildGameObject(this, m_Element, LAYER_TYPE::ELEMENT);

	}
	// �ҿ� 1�� �̻� Ÿ�� �ִٸ�
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
	// ���� ���� �ʾҴٸ�
	if (!IsValid(m_Element))
	{
		// �� ȿ�� ���� �߰�
		// �� �����̻��� ������ Enter�� �ѹ� �ߵ� �ǹǷ� ��� ��Ÿ�� ����
		// �����̻� ���� �ڽ�
		m_Element = new GFire;
		CreateChildGameObject(this, m_Element, LAYER_TYPE::ELEMENT);

	}
}



