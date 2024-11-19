#include "pch.h"
#include "GPMoveState.h"

#include "GPlayer.h"

#include "GFlipBookPlayer.h"
#include "GRigidBody.h"

GPMoveState::GPMoveState() :
	m_Player(nullptr),
	m_PlayerInfo(nullptr),
	m_PrevDir()
{
}

GPMoveState::~GPMoveState()
{
}

void GPMoveState::Awake()
{
	m_Player = dynamic_cast<GPlayer*>(GetOwnerObj());
	assert(m_Player != nullptr);

	m_PlayerInfo = (PlayerInfo*)m_Player->GetPlayerStatInfo();
}

void GPMoveState::Enter()
{
	m_Player->m_FlipBookPlayer->Play();
}

void GPMoveState::FinalTick()
{
	// 방향키를 안누르고 있다면 IDLE 상태로 변경
	if (GETKEYNONE(KEY::LEFT) && GETKEYNONE(KEY::RIGHT) && GETKEYNONE(KEY::DOWN) && GETKEYNONE(KEY::UP))
	{
		m_Player->m_FSM->ChanageState(L"IDLE");
	}
	else if (GETKEYDOWN(KEY::SPACE))
	{
		if (m_Player->m_WeaponEquip != CREATURE_ID::END)
			m_Player->m_FSM->ChanageState(L"ATTACK");
		else if (m_Player->m_ToolEquip != CREATURE_ID::END)
			m_Player->m_FSM->ChanageState(L"TOOL");
	}
	else if (GETKEYDOWN(KEY::C))
	{
		m_Player->PickUpItem();
	}
	else if (GETKEYDOWN(KEY::Z))
	{
		m_Player->UseItem();
	}
	else if (GETKEYDOWN(KEY::X))
	{
		m_Player->DropInvenItem();
	}

	// 이동 방향
	if (GETKEYPRESSED(KEY::UP))
	{
		m_PlayerInfo->Direction = Vec2::up();
	}
	else if (GETKEYPRESSED(KEY::DOWN))
	{
		m_PlayerInfo->Direction = Vec2::down();
	}
	else if (GETKEYPRESSED(KEY::LEFT))
	{
		m_PlayerInfo->Direction = Vec2::left();
	}
	else if (GETKEYPRESSED(KEY::RIGHT))
	{
		m_PlayerInfo->Direction = Vec2::right();
	}

	if (m_PrevDir != m_PlayerInfo->Direction)
	{
		if (m_PlayerInfo->Direction == Vec2::up())
		{
			m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::UP, 5, true);
		}
		else if (m_PlayerInfo->Direction == Vec2::down())
		{
			m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::DOWN, 5, true);
		}
		else if (m_PlayerInfo->Direction == Vec2::left())
		{
			m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::RIGHT, 5, true);
			m_Player->m_FlipBookPlayer->SetXFlip(true);
		}
		else if (m_PlayerInfo->Direction == Vec2::right())
		{
			m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::RIGHT, 5, true);
			m_Player->m_FlipBookPlayer->SetXFlip(false);
		}
		m_PrevDir = m_PlayerInfo->Direction;
	}
	
	m_Player->m_RigidBody->SetVelocity(m_PlayerInfo->Direction * m_PlayerInfo->Speed);
}

void GPMoveState::Exit()
{
	m_Player->m_RigidBody->SetVelocity(Vec2::zero());
}
