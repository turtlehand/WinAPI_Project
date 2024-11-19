#include "pch.h"
#include "GMBeAttackedState.h"

#include "GMonster.h"
#include "GFlipBookPlayer.h"

#include "GAssetManager.h"
#include "GSound.h"

GMBeAttackedState::GMBeAttackedState() :
	m_Monster(nullptr),
	m_Timer(0.5f),
	m_EnemyHurt(nullptr)
{
}

GMBeAttackedState::~GMBeAttackedState()
{
}

void GMBeAttackedState::Awake()
{
	m_Monster = dynamic_cast<GMonster*>(GetOwnerObj());
	assert(m_Monster != nullptr);

	m_EnemyHurt = GAssetManager::GetInst()->LoadSound(L"Enemy_Hit", L"Sound\\Sound_Effects\\LOZ_Enemy_Hit.wav");
	m_EnemyHurt->SetVolume(100.f);
}

void GMBeAttackedState::Enter()
{
	m_Monster->m_FlipBookPlayer->Pause();
	m_Monster->m_FlipBookPlayer->SetAlpha(128);
	m_Timer = 0.5f;
	m_Monster->GetStatInfo()->IsInvincible = true;

	m_EnemyHurt->Play();
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