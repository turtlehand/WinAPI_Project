#include "pch.h"
#include "GPIdleState.h"

#include "GPlayer.h"

#include "GFlipBookPlayer.h"

GPIdleState::GPIdleState() :
	m_Player(nullptr)
{
}

GPIdleState::~GPIdleState()
{
}

void GPIdleState::Awake()
{
	m_Player = dynamic_cast<GPlayer*>(GetOwnerObj());
	assert(m_Player != nullptr);
}

void GPIdleState::Enter()
{
	m_Player->m_FlipBookPlayer->Pause();
}

void GPIdleState::FinalTick()
{
	if (GETKEYPRESSED(KEY::UP) || GETKEYPRESSED(KEY::DOWN) || GETKEYPRESSED(KEY::LEFT) || GETKEYPRESSED(KEY::RIGHT))
	{
		m_Player->m_FSM->ChanageState(L"MOVE");
	}
	else if (GETKEYDOWN(KEY::SPACE))
	{
		if(m_Player->m_WeaponEquip != CREATURE_ID::END)
			m_Player->m_FSM->ChanageState(L"ATTACK");
		else if(m_Player->m_ToolEquip != CREATURE_ID::END)
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
}

void GPIdleState::Exit()
{

}
