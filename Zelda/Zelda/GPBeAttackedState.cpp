#include "pch.h"
#include "GPBeAttackedState.h"

#include "GPlayer.h"

#include "GFlipBookPlayer.h"

GPBeAttackedState::GPBeAttackedState() :
	m_Player(nullptr),
	m_Timer(0.f)
{
}

GPBeAttackedState::~GPBeAttackedState()
{
}

void GPBeAttackedState::Begin()
{
	m_Player = dynamic_cast<GPlayer*>(GetOwnerObj());
	assert(m_Player != nullptr);
}

void GPBeAttackedState::Enter()
{
	m_Player->m_FlipBookPlayer->Pause();
	m_Timer = 0.5f;
	m_Player->GetStatInfo()->IsInvincible = true;
}

void GPBeAttackedState::FinalTick()
{
	m_Timer -= DT;
	m_Player->m_FlipBookPlayer->SetAlpha(128);
	if (m_Timer < 0.f)
		m_Player->m_FSM->ChanageState(L"IDLE");
}

void GPBeAttackedState::Exit()
{
	m_Player->m_FlipBookPlayer->SetAlpha(255);
	m_Player->m_FlipBookPlayer->Play();
	m_Player->GetStatInfo()->IsInvincible = false;
}