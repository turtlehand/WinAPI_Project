#include "pch.h"
#include "GPDieState.h"

#include "GPlayer.h"

#include "GAssetManager.h"
#include "GSound.h"
#include "GRigidBody.h"
#include "GSoundManager.h"

GPDieState::GPDieState() : m_Player(nullptr)
{
}

GPDieState::~GPDieState()
{
}

void GPDieState::Awake()
{
	m_Player = dynamic_cast<GPlayer*>(GetOwnerObj());
	assert(m_Player != nullptr);
}

void GPDieState::Enter()
{
	GSoundManager::GetInst()->RegisterToBGM(nullptr);
	GAssetManager::GetInst()->LoadSound(L"Link_Die", L"Sound\\Sound_Effects\\LOZ_Link_Die.wav")->Play();
	m_Player->m_FlipBookPlayer->SetPlay(0, 8, true);
	m_Player->GetStatInfo()->IsInvincible = true;
	int rgb = RGB(-1, -1, -1);
}

void GPDieState::FinalTick()
{

	m_Player->m_RigidBody->SetVelocity(Vec2(0.f, 0.f));
	if (m_Player->m_FlipBookPlayer->IsFinish())
		ChangeLevel(LEVEL_TYPE::START);
}

void GPDieState::Exit()
{

}