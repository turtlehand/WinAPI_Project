#include "pch.h"
#include "GPAttackState.h"

#include "Player.h"

#include "GFlipBookPlayer.h"

GPAttackState::GPAttackState() :
	m_Player(nullptr),
	m_PlayerInfo(nullptr)
{
}

GPAttackState::~GPAttackState()
{
}

void GPAttackState::Awake()
{
	m_Player = dynamic_cast<Player*>(GetOwnerObj());
	assert(m_Player != nullptr);

	m_PlayerInfo = &(m_Player->m_PlayerInfo);
}

void GPAttackState::Enter()
{
	m_PrevAnim = (PLAYER_ANIM_STATE)m_Player->m_FlipBookPlayer->GetCurIndex();

	if (m_PlayerInfo->Direction == Vec2::up())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_UP, 10, false);
	}
	else if (m_PlayerInfo->Direction == Vec2::down())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_DOWN, 10, false);
	}
	else if (m_PlayerInfo->Direction == Vec2::left())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 10, false);
		m_Player->m_FlipBookPlayer->SetXFlip(true);
	}
	else if(m_PlayerInfo->Direction == Vec2::right())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 10, false);
		m_Player->m_FlipBookPlayer->SetXFlip(false);
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
	m_Player->m_FlipBookPlayer->SetPlay((int)m_PrevAnim, 5, true);
}
