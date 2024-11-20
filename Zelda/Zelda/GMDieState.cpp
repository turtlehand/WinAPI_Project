#include "pch.h"
#include "GMDieState.h"

#include "GMonster.h"

#include "GAssetManager.h"
#include "GSound.h"
#include "GRigidBody.h"
#include "GHitBox.h"

GMDieState::GMDieState() : m_Monster(nullptr)
{
}

GMDieState::~GMDieState()
{
}

void GMDieState::Awake()
{
	m_Monster = dynamic_cast<GMonster*>(GetOwnerObj());
	assert(m_Monster != nullptr);
}

void GMDieState::Enter()
{
	GAssetManager::GetInst()->LoadSound(L"Enemy_Die", L"Sound\\Sound_Effects\\LOZ_Enemy_Die.wav")->Play();
	m_Monster->m_FlipBookPlayer->SetPlay(0, 8, false);
	m_Monster->GetStatInfo()->IsInvincible = true;
	m_Monster->GetAttackBox()->SetActive(false);
}

void GMDieState::FinalTick()
{

	m_Monster->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	if (m_Monster->m_FlipBookPlayer->IsFinish())
		DeleteGameObject(m_Monster);
}

void GMDieState::Exit()
{

}


