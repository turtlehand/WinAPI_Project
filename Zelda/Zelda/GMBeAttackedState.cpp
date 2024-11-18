#include "pch.h"
#include "GMBeAttackedState.h"

#include "GMonster.h"
#include "GFlipBookPlayer.h"

GMBeAttackedState::GMBeAttackedState() :
	m_Monster(nullptr),
	m_Timer(0.5f)
{
}

GMBeAttackedState::~GMBeAttackedState()
{
}

void GMBeAttackedState::Begin()
{
	m_Monster = dynamic_cast<GMonster*>(GetOwnerObj());
	assert(m_Monster != nullptr);
}

void GMBeAttackedState::Enter()
{
	m_Monster->m_FlipBookPlayer->Pause();
	m_Monster->m_FlipBookPlayer->SetAlpha(128);
	m_Timer = 0.5f;
	m_Monster->GetStatInfo()->IsInvincible = true;
}

void GMBeAttackedState::FinalTick()
{
	m_Timer -= DT;
	if (m_Timer < 0.f)
		m_Monster->m_FSM->ChanageState(L"IDLE");
}

void GMBeAttackedState::Exit()
{
	m_Monster->m_FlipBookPlayer->Play();
	m_Monster->m_FlipBookPlayer->SetAlpha(255);
	m_Monster->GetStatInfo()->IsInvincible = false;
}