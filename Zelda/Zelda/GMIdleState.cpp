#include "pch.h"
#include "GMIdleState.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "GMonster.h"

#include "GFlipBookPlayer.h"

GMIdleState::GMIdleState() :
	m_Monster(nullptr)
{

}

GMIdleState::~GMIdleState()
{
}

void GMIdleState::Begin()
{
	m_Monster = dynamic_cast<GMonster*>(GetOwnerObj());
	assert(m_Monster != nullptr);
}

void GMIdleState::Enter()
{
	m_Monster->m_FlipBookPlayer->Pause();
}

void GMIdleState::FinalTick()
{

	if (!IsValid(m_Monster->m_Target))
		m_Monster->m_Target = CLevelMgr::GetInst()->GetCurrentLevel()->FindGameObject(L"Player", LAYER_TYPE::PLAYER);

	if (IsValid(m_Monster->m_Target))
	{
		Vec2 vTargetPos = m_Monster->m_Target->GetGlobalPos();
		Vec2 vPos = m_Monster->GetGlobalPos();
		float Distance = sqrtf(powf(vTargetPos.x - vPos.x, 2) + powf(vTargetPos.y - vPos.y, 2));

		if (m_Monster->GetMonsterStatInfo()->DetectRange > Distance)
		{
			m_Monster->m_FSM->ChanageState(L"CHASE");
		}
	}

	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetGlobalPos(), m_Monster->GetMonsterStatInfo()->DetectRange);
}

void GMIdleState::Exit()
{

}


