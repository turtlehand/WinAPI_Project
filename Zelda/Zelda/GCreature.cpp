#include "pch.h"
#include "GCreature.h"

#include "GAssetManager.h"

#include "GHitBox.h";
#include "GFlipBookPlayer.h"

GCreature::GCreature() :
	m_StatInfo(nullptr),
	m_EffectAnim(nullptr)
{
	m_EffectAnim = AddComponent<GFlipBookPlayer>();
	//m_EffectAnim->SetScale(Vec2(4.f, 4.f));

	m_EffectAnim->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"FIRE", L"FlipBook\\NPC_16\\FIRE.flip"));

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

void GCreature::StatusEffect()
{
	if (m_StatInfo->Effect.ElementType == ELEMENT_TYPE::NONE)
		return;

	if (m_StatInfo->Effect.Time < 0.f)
	{
		m_EffectAnim->SetPlay(-1, 4, true);
		m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
		m_StatInfo->Effect.Duration = 0.f;
		m_StatInfo->Effect.Time = 0.f;
	}

	m_StatInfo->Effect.Time -= DT;

	if (m_StatInfo->Effect.ElementType == ELEMENT_TYPE::FIRE)
	{
		// 1초가 지날 때마다 피해를 입음
		if (m_StatInfo->Effect.Duration - m_StatInfo->Effect.Time >= 1)
		{
			Damaged(1);
			m_StatInfo->Effect.Duration = m_StatInfo->Effect.Time;
		}
	}
		
}

void GCreature::Interaction(GHitBox* _HitBox)
{
	if (m_StatInfo->IsDead)
		return;

	ATTACK_TYPE HBAttackType = _HitBox->GetAttackType();
	ELEMENT_TYPE HBElementType = _HitBox->GetEffect().ElementType;

	MATERIAL_TYPE CMaterialType = m_StatInfo->Material;
	ELEMENT_TYPE CElementType = m_StatInfo->Effect.ElementType;

	// 소재 - 공격 반응
	if (CMaterialType == MATERIAL_TYPE::STONE && HBAttackType == ATTACK_TYPE::STRIKE)
		Smash();
	else if (HBAttackType != ATTACK_TYPE::NONE && CMaterialType == MATERIAL_TYPE::LIFE)
		BeAttacked(_HitBox->GetDamage());
	else if (CMaterialType == MATERIAL_TYPE::WOOD && HBAttackType == ATTACK_TYPE::SLASH)
		CutWood();

	// 소재 - 속성 반응
	if (CMaterialType == MATERIAL_TYPE::METAL && HBElementType == ELEMENT_TYPE::LIGHTNING)
		Flow();
	else if ((CMaterialType == MATERIAL_TYPE::WOOD || CMaterialType == MATERIAL_TYPE::LIFE) &&
		HBElementType == ELEMENT_TYPE::FIRE)
		Burn();
	else if (CMaterialType == MATERIAL_TYPE::LIFE && HBElementType == ELEMENT_TYPE::LIGHTNING)
		Shock();
	else if (CMaterialType == MATERIAL_TYPE::LIFE && HBElementType == ELEMENT_TYPE::ICE)
		Freeze();

	// 속성 - 속성 반응
	if (CElementType == ELEMENT_TYPE::FIRE &&
		(HBElementType == ELEMENT_TYPE::ICE || HBElementType == ELEMENT_TYPE::WATER))
		Extinguish();
	else if (CElementType == ELEMENT_TYPE::WATER && HBElementType == ELEMENT_TYPE::LIGHTNING)
		Flow();
	else if (CElementType == ELEMENT_TYPE::WATER && HBElementType == ELEMENT_TYPE::ICE)
		Freeze();
	else if (CElementType == ELEMENT_TYPE::ICE && HBElementType == ELEMENT_TYPE::FIRE)
		Melt();

	InteractionEffect();
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
	m_StatInfo->Effect.Duration = 5.f;
	m_StatInfo->Effect.Time = 5.f;
	m_EffectAnim->SetPlay((int)ELEMENT_TYPE::FIRE, 10, true);
}

void GCreature::Flow()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::LIGHTNING;
	m_StatInfo->Effect.Duration = 1.f;
	m_StatInfo->Effect.Time = 1.f;
}

void GCreature::Shock()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::LIGHTNING;
	m_StatInfo->Effect.Duration = 1.f;
	m_StatInfo->Effect.Time = 1.f;

	// 추가로 무기 떨구기
}

void GCreature::Freeze()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::ICE;
	m_StatInfo->Effect.Duration = 30.f;
	m_StatInfo->Effect.Time = 30.f;

}

void GCreature::Wet()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::WATER;
	m_StatInfo->Effect.Duration = 30.f;
	m_StatInfo->Effect.Time = 30.f;
}

void GCreature::Extinguish()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	m_StatInfo->Effect.Duration = 0.f;
	m_StatInfo->Effect.Time = 0.f;
}

void GCreature::Melt()
{
	m_StatInfo->Effect.ElementType = ELEMENT_TYPE::NONE;
	m_StatInfo->Effect.Duration = 0.f;
	m_StatInfo->Effect.Time = 0.f;
}

void GCreature::KnockBack()
{

}


