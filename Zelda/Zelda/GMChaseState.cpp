#include "pch.h"
#include "GMChaseState.h"

#include "Monster.h"

GMChaseState::GMChaseState() :
	m_Monster(nullptr)
{

}

GMChaseState::~GMChaseState()
{

}

void GMChaseState::Awake()
{
	m_Monster = dynamic_cast<Monster*>(GetOwnerObj());
	assert(m_Monster != nullptr);
}

void GMChaseState::Enter()
{

}

void GMChaseState::FinalTick()
{
	// 추적 대상이 없다면 상태를 바꾼다.
	if (!IsValid(m_Monster->m_Target))
		m_Monster->m_FSM->ChanageState(L"IDLE");

	// 몬스터의 이동속도에 맞게ㅔ 플레이어를 향해서 이동한다.
	m_Monster->m_Dir = (m_Monster->m_Target->GetPos() - m_Monster->GetPos()).Normalize();

	// 해당 방향으로, 속ㄹ력에 맞게 매프레임마다 이동
	Vec2 vPos = m_Monster->GetPos()+  m_Monster->m_Dir * m_Monster->GetInfo().Speed * DT;
	m_Monster->SetPos(vPos);

	// 인지 범위 시각화
	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetPos(), m_Monster->GetInfo().DetectRange);

}

void GMChaseState::Exit()
{
}


