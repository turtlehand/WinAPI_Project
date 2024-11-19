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
	// ���� ����� ���ٸ� ���¸� �ٲ۴�.
	if (!IsValid(m_Monster->m_Target))
		m_Monster->m_FSM->ChanageState(L"IDLE");
	// ���� ���� �Ÿ��� ����ٸ� ���¸� �����Ѵ�.
	else if ((m_Monster->m_Target->GetGlobalPos() - m_Monster->GetGlobalPos()).Length() > m_MonsterInfo->DetectKeepRange)
	{
		m_Monster->m_FSM->ChanageState(L"IDLE");
		return;
	}


	// ���Ͱ� ������ ������ �˾Ƴ���.
	Vec2 Direction = (m_Monster->m_Target->GetGlobalPos() - m_Monster->GetGlobalPos()).Normalize();

	// x�� ������ �� ũ�ٸ�
	if (fabs(Direction.x) > fabs(Direction.y))
	{
		// x �� �������� �̵��Ѵ�.
		m_MonsterInfo->Direction = Vec2(Direction.x, 0.f);
	}
	else
	{
		// y �� �������� �̵��Ѵ�.
		m_MonsterInfo->Direction = Vec2(0.f, Direction.y);
	}
	m_MonsterInfo->Direction = m_MonsterInfo->Direction.Normalize();


	// �ش� ��������, �ӷ¿� �°� �������Ӹ��� �̵�
	m_Monster->GetRigidBody()->SetVelocity(m_Monster->GetMonsterStatInfo()->Direction * m_Monster->GetMonsterStatInfo()->Speed);

	// ���� ���� �ð�ȭ
	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetGlobalPos(), m_Monster->GetMonsterStatInfo()->DetectKeepRange);


	// ������ �ٲ� ������ �ִϸ��̼��� ���� �����ش�.
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


