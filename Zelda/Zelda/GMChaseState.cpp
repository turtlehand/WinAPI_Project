#include "pch.h"
#include "GMChaseState.h"

#include "GMonster.h"
#include "GRigidBody.h"
#include "GFlipBookPlayer.h"

GMChaseState::GMChaseState() :
	m_Monster(nullptr)
{

}

GMChaseState::~GMChaseState()
{

}

void GMChaseState::Awake()
{
	m_Monster = dynamic_cast<GMonster*>(GetOwnerObj());
	assert(m_Monster != nullptr);

	m_MonsterInfo = m_Monster->GetMonsterStatInfo();
}

void GMChaseState::Enter()
{
	m_Monster->GetFlipBookPlayer()->Play();
	m_PrevDir = Vec2::zero();
}

void GMChaseState::FinalTick()
{
	// 추적 대상이 없다면 상태를 바꾼다.
	if (!IsValid(m_Monster->m_Target))
		m_Monster->m_FSM->ChanageState(L"IDLE");
	// 감지 유지 거리를 벗어났다면 상태를 변경한다.
	else if ((m_Monster->m_Target->GetGlobalPos() - m_Monster->GetGlobalPos()).Length() > m_MonsterInfo->DetectKeepRange)
	{
		m_Monster->m_FSM->ChanageState(L"IDLE");
		return;
	}


	// 몬스터가 가야할 방향을 알아낸다.
	Vec2 Direction = (m_Monster->m_Target->GetGlobalPos() - m_Monster->GetGlobalPos()).Normalize();

	// x축 방향이 더 크다면
	if (fabs(Direction.x) > fabs(Direction.y))
	{
		// x 축 방향으로 이동한다.
		m_MonsterInfo->Direction = Vec2(Direction.x, 0.f);
	}
	else
	{
		// y 축 방향으로 이동한다.
		m_MonsterInfo->Direction = Vec2(0.f, Direction.y);
	}
	m_MonsterInfo->Direction = m_MonsterInfo->Direction.Normalize();


	// 해당 방향으로, 속력에 맞게 매프레임마다 이동
	m_Monster->GetRigidBody()->SetVelocity(m_Monster->GetMonsterStatInfo()->Direction * m_Monster->GetMonsterStatInfo()->Speed);

	// 인지 범위 시각화
	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetGlobalPos(), m_Monster->GetMonsterStatInfo()->DetectKeepRange);


	// 방향이 바뀔 때마다 애니메이션을 변경 시켜준다.
	if (m_PrevDir != m_MonsterInfo->Direction)
	{
		if (m_MonsterInfo->Direction == Vec2::up())
		{
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::UP, 5, true);
		}
		else if (m_MonsterInfo->Direction == Vec2::down())
		{
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::DOWN, 5, true);
		}
		else if (m_MonsterInfo->Direction == Vec2::left())
		{
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::RIGHT, 5, true);
			m_Monster->m_FlipBookPlayer->SetXFlip(true);
		}
		else if (m_MonsterInfo->Direction == Vec2::right())
		{
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::RIGHT, 5, true);
			m_Monster->m_FlipBookPlayer->SetXFlip(false);
		}
		m_PrevDir = m_MonsterInfo->Direction;
	}

}

void GMChaseState::Exit()
{
	m_Monster->SetTarget(nullptr);
}


