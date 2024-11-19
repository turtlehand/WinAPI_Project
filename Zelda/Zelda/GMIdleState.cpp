#include "pch.h"
#include "GMIdleState.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "GMonster.h"

#include "GFlipBookPlayer.h"
#include "GRigidBody.h"

GMIdleState::GMIdleState() :
	m_Monster(nullptr),
	m_MonsterInfo(nullptr),
	m_MoveTimer(0.f)
{

}

GMIdleState::~GMIdleState()
{
}

void GMIdleState::Awake()
{
	m_Monster = dynamic_cast<GMonster*>(GetOwnerObj());
	assert(m_Monster != nullptr);

	m_MonsterInfo = m_Monster->GetMonsterStatInfo();
}

void GMIdleState::Enter()
{
	// 3�� �� ������ �ٲ۴�.
	m_MoveTimer = 3.f;
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

	// Ÿ�̸Ӹ� �����Ų��.
	m_MoveTimer -= DT;

	// �ش� �������� �̵��Ѵ�.
	m_Monster->GetRigidBody()->SetVelocity(m_Monster->GetMonsterStatInfo()->Direction * m_Monster->GetMonsterStatInfo()->Speed);

	// Ž�� �Ÿ��� ǥ���Ѵ�.
	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetGlobalPos(), m_Monster->GetMonsterStatInfo()->DetectRange);

	// Ÿ�̸��� �ð��� �� ������ ������ �ٲ۴�.
	if (m_MoveTimer <= 0)
	{

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, 4);

		int RandomIndex = dist(gen);

		switch (RandomIndex)
		{
		case 0:
			m_MonsterInfo->Direction = Vec2::up();
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::UP, 5, true);
			break;
		case 1:
			m_MonsterInfo->Direction = Vec2::down();
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::DOWN, 5, true);
			break;

		case 2:
			m_MonsterInfo->Direction = Vec2::left();
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::RIGHT, 5, true);
			m_Monster->m_FlipBookPlayer->SetXFlip(true);
			break;

		case 3:
			m_MonsterInfo->Direction = Vec2::right();
			m_Monster->m_FlipBookPlayer->SetPlay((int)MOBLIN_ANIM_STATE::RIGHT, 5, true);
			m_Monster->m_FlipBookPlayer->SetXFlip(false);
			break;
		default:
			break;
		}

		// ���� ���� ��ȯ���� �ð�
		m_MoveTimer = dist(gen);
	}
}

void GMIdleState::Exit()
{

}


