#include "pch.h"
#include "GCreature.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "GAssetManager.h"

#include "GBoxCollider.h"

#include "GHitBox.h";
#include "GFlipBookPlayer.h"

GCreature::GCreature(CREATURE_ID _CreatrueID) :
	m_CreatureID(_CreatrueID),
	m_StatInfo(nullptr),
	m_HitBox(nullptr),
	m_Effect(nullptr)
{
	m_HitBox = AddComponent<GBoxCollider>();

	//m_EffectAnim->SetDeleteColor(RGB(116, 116, 116));
}

GCreature::~GCreature()
{
	delete m_StatInfo;
}

void GCreature::Tick()
{
	StatusEffect();
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

	if (m_StatInfo->Effect.ElementType == ELEMENT_TYPE::FIRE)
	{
		Ignite();
	}

	m_StatInfo->Effect.Time -= DT;

	if (m_StatInfo->Effect.Time < 0)
	{
		m_StatInfo->Effect.Time = 0.f;
		m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	}

}

void GCreature::Interaction_Element(GCreature* _Creature)
{
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
	// ���� ���翡 ������ ��´ٸ�

	ATTACK_TYPE HBAttackType = _HitBox->GetAttackType();

	MATERIAL_TYPE CMaterialType = m_StatInfo->Material;

	// ���� - ���� ����
	if (CMaterialType == MATERIAL_TYPE::STONE && HBAttackType == ATTACK_TYPE::STRIKE)
		Smash();
	else if (CMaterialType == MATERIAL_TYPE::LIFE && HBAttackType != ATTACK_TYPE::NONE )
		BeAttacked(_HitBox->GetDamage());
	else if (CMaterialType == MATERIAL_TYPE::WOOD && HBAttackType == ATTACK_TYPE::SLASH)
		CutWood();

	InteractionEffect_Attack(_HitBox);
}

void GCreature::Damaged(int _Damage)
{
	if (m_StatInfo->IsDead)
		return;

	m_StatInfo->HP -= _Damage;

	if (m_StatInfo->HP <= 0)
		Dead();
}

void GCreature::Dead()
{
	DropItem();
	m_StatInfo->IsDead = true;
	DeleteGameObject(this);
}

void GCreature::Smash()
{
	if (m_StatInfo->Material != MATERIAL_TYPE::STONE)
		return;

	Damaged(2);
}

void GCreature::CutWood()
{
	if (m_StatInfo->Material != MATERIAL_TYPE::WOOD)
		return;

	Damaged(2);
}

void GCreature::BeAttacked(int _Damage)
{
	Damaged(_Damage);
	KnockBack();
}

void GCreature::Burn()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::FIRE;
	m_StatInfo->Effect.Time += 2 * DT;
}

void GCreature::Flow()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::LIGHTNING;
	m_StatInfo->Effect.Time = 1.f;
}

void GCreature::Shock()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::LIGHTNING;
	m_StatInfo->Effect.Time = 1.f;

	// �߰��� ���� ������
}

void GCreature::Freeze()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::ICE;
	m_StatInfo->Effect.Time = 30.f;

}

void GCreature::Wet()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::WATER;
	m_StatInfo->Effect.Time = 30.f;
}

void GCreature::Extinguish()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	m_StatInfo->Effect.Time = 0.f;
}

void GCreature::Melt()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	m_StatInfo->Effect.Time = 0.f;
}

void GCreature::KnockBack()
{

}

void GCreature::Ignite()
{
	// ���� ���� �ʾҰ� 1�� �̻� Ÿ�� �ִٸ�
	if (m_StatInfo->Effect.Time > 0.5f && !IsValid(m_Effect))
	{
		//Damaged(1);
		m_StatInfo->Effect.Time -= 0.5f;

		// �� ȿ�� ���� �߰�
		// �� �����̻��� ������ Enter�� �ѹ� �ߵ� �ǹǷ� ��� ��Ÿ�� ����
		// �����̻� ���� �ڽ�
		m_Effect = new GHitBox;
		m_Effect->SetName(L"Effect Box");
		(m_Effect->GetComponent<GBoxCollider>())->SetScale(m_HitBox->GetScale());
		(m_Effect->GetComponent<GBoxCollider>())->SetTrigger(true);
		((GHitBox*)m_Effect)->m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"FIRE", L"FlipBook\\NPC_16\\FIRE.flip"));
		((GHitBox*)m_Effect)->m_FlipBookPlayer->SetPlay(0, 4, true);
		((GHitBox*)m_Effect)->GetStatInfo()->Material = MATERIAL_TYPE::FIRE;

		CreateChildGameObject(this, m_Effect, LAYER_TYPE::ELEMENT);

	}
	// �ҿ� 1�� �̻� Ÿ�� �ִٸ�
	else if (m_StatInfo->Effect.Time > 1.f)
	{
		Damaged(1);
		m_StatInfo->Effect.Time -= 1.f;
		m_StatInfo->Effect.Duration += 1.f;
	}
	// ���ӽð��� ������ ���� ����.
	else if (m_StatInfo->Effect.Duration > 5.f)
	{
		DeleteGameObject(m_Effect);
		m_Effect = nullptr;
		m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
		m_StatInfo->Effect.Time = 0.f;
		m_StatInfo->Effect.Duration = 0.f;
	}
}

void GCreature::InstantIgnite()
{
	// ���� ���� �ʾҴٸ�
	if (!IsValid(m_Effect))
	{
		// �� ȿ�� ���� �߰�
		// �� �����̻��� ������ Enter�� �ѹ� �ߵ� �ǹǷ� ��� ��Ÿ�� ����
		// �����̻� ���� �ڽ�
		m_Effect = new GHitBox;
		m_Effect->SetName(L"Effect Box");
		(m_Effect->GetComponent<GBoxCollider>())->SetScale(m_HitBox->GetScale());
		(m_Effect->GetComponent<GBoxCollider>())->SetTrigger(true);
		((GHitBox*)m_Effect)->m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"FIRE", L"FlipBook\\NPC_16\\FIRE.flip"));
		((GHitBox*)m_Effect)->m_FlipBookPlayer->SetPlay(0, 4, true);
		((GHitBox*)m_Effect)->GetStatInfo()->Material = MATERIAL_TYPE::FIRE;

		CreateChildGameObject(this, m_Effect, LAYER_TYPE::ELEMENT);

	}
}



