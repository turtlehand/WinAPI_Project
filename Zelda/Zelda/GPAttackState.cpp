#include "pch.h"
#include "GPAttackState.h"

#include "GPlayer.h"
#include "GHitBox.h"
#include "GBoxCollider.h"

#include "GFlipBookPlayer.h"

GPAttackState::GPAttackState() :
	m_Player(nullptr),
	m_PlayerInfo(nullptr),
	m_AttackBox(nullptr),
	m_PrevAnim(PLAYER_ANIM_STATE::NONE)
{
}

GPAttackState::~GPAttackState()
{
}

void GPAttackState::Begin()
{
	m_Player = dynamic_cast<GPlayer*>(GetOwnerObj());
	assert(m_Player != nullptr);

	m_PlayerInfo = m_Player->GetPlayerStatInfo();
	m_AttackBox = m_Player->m_AttackBox;
}

void GPAttackState::Enter()
{
	m_PrevAnim = (PLAYER_ANIM_STATE)m_Player->m_FlipBookPlayer->GetCurIndex();

	m_AttackBox->SetAttackType(ATTACK_TYPE::SLASH);
	m_AttackBox->SetMaterialType(MATERIAL_TYPE::METAL);
	m_AttackBox->SetEffect({ ELEMENT_TYPE::FIRE,0.f,0.f });
	m_AttackBox->SetDamage(1);
	m_AttackBox->SetActive(true);

	if (m_PlayerInfo->Direction == Vec2::up())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_UP, 4.f, false);

		m_AttackBox->SetPos(0.f, 64.f);
		((GBoxCollider*)m_AttackBox->m_Collider)->SetScale(Vec2(32.f, 64.f));
	}
	else if (m_PlayerInfo->Direction == Vec2::down())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_DOWN, 4.f, false);

		m_AttackBox->SetPos(0.f, -64.f);
		((GBoxCollider*)m_AttackBox->m_Collider)->SetScale(Vec2(32.f, 64.f));
	}
	else if (m_PlayerInfo->Direction == Vec2::left())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 4.f, false);
		m_Player->m_FlipBookPlayer->SetXFlip(true);

		m_AttackBox->SetPos(-64.f, 0);
		((GBoxCollider*)m_AttackBox->m_Collider)->SetScale(Vec2(64.f, 32.f));
	}
	else if(m_PlayerInfo->Direction == Vec2::right())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 4.f, false);
		m_Player->m_FlipBookPlayer->SetXFlip(false);

		m_AttackBox->SetPos(64.f, 0);
		((GBoxCollider*)m_AttackBox->m_Collider)->SetScale(Vec2(64.f, 32.f));
	}


	
	m_Player->m_FlipBookPlayer->Reset();
	m_Player->m_FlipBookPlayer->Play();
}

void GPAttackState::FinalTick()
{
	if (m_Player->m_FlipBookPlayer->IsFinish())
	{
		
		m_Player->m_FSM->ChanageState(L"IDLE");
	}
}

void GPAttackState::Exit()
{
	m_AttackBox->SetActive(false);
	m_Player->m_FlipBookPlayer->SetPlay((int)m_PrevAnim, 5, true);
}
