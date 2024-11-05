#include "pch.h"
#include "GCreature.h"

#include "GHitBox.h";

GCreature::GCreature() :
	m_StatInfo(nullptr)
{
}

GCreature::~GCreature()
{
	delete m_StatInfo;
}

void GCreature::BeAttacked(GHitBox* _HitBox)
{
	if (m_StatInfo->IsDead)
		return;

	ATTACK_TYPE AttackType = _HitBox->GetAttackType();
	MATERIAL_TYPE MaterialType = m_StatInfo->Material;

	if (AttackType == ATTACK_TYPE::STRIKE && MaterialType == MATERIAL_TYPE::STONE)
	{
		Smash();
	}
	else if ((AttackType == ATTACK_TYPE::SLASH || AttackType == ATTACK_TYPE::THRUSHT) &&
		(MaterialType == MATERIAL_TYPE::STONE || MaterialType == MATERIAL_TYPE::METAL))
	{

	}
	// 아무런 상호작용 없음
	else
	{
		if (m_StatInfo->Material == MATERIAL_TYPE::WOOD || m_StatInfo->Material == MATERIAL_TYPE::STONE)
		{
			Damaged(1);
		}
		else if (m_StatInfo->Material == MATERIAL_TYPE::LIFE)
		{
			Damaged(_HitBox->GetDamage());
		}
		else if (m_StatInfo->Material == MATERIAL_TYPE::METAL)
		{

		}
		
	}

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
	m_StatInfo->IsDead = true;
	DeleteGameObject(this);
}

void GCreature::Smash()
{
	if (m_StatInfo->Material != MATERIAL_TYPE::STONE)
		return;

	Damaged(2);
}

void GCreature::KnockBack()
{
}


