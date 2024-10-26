#include "pch.h"
#include "GMIdleState.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "Monster.h"

GMIdleState::GMIdleState() :
	m_Monster(nullptr)
{

}

GMIdleState::~GMIdleState()
{
}

void GMIdleState::Awake()
{
	m_Monster = dynamic_cast<Monster*>(GetOwnerObj());
	assert(m_Monster != nullptr);
}

void GMIdleState::Enter()
{

}

void GMIdleState::FinalTick()
{
	// 
	if (!IsValid(m_Monster->m_Target))
		m_Monster->m_Target = CLevelMgr::GetInst()->GetCurrentLevel()->FindGameObject(L"Player", LAYER_TYPE::PLAYER);

	if (IsValid(m_Monster->m_Target))
	{
		Vec2 vTargetPos = m_Monster->m_Target->GetPos();
		Vec2 vPos = m_Monster->GetPos();
		float Distance = sqrtf(powf(vTargetPos.x - vPos.x, 2) + powf(vTargetPos.y - vPos.y, 2));

		if (m_Monster->GetInfo().DetectRange > Distance)
		{
			//m_Monster->m_FSM->ChanageState(L"CHASE");
		}
	}

	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetPos(), m_Monster->GetInfo().DetectRange);
}

void GMIdleState::Exit()
{

}


