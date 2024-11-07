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

void GMChaseState::Begin()
{
	m_Monster = dynamic_cast<GMonster*>(GetOwnerObj());
	assert(m_Monster != nullptr);
}

void GMChaseState::Enter()
{
	m_Monster->GetFlipBookPlayer()->Play();
}

void GMChaseState::FinalTick()
{
	// ���� ����� ���ٸ� ���¸� �ٲ۴�.
	if (!IsValid(m_Monster->m_Target))
		m_Monster->m_FSM->ChanageState(L"IDLE");

	// ������ �̵��ӵ��� �°Ԥ� �÷��̾ ���ؼ� �̵��Ѵ�.
	m_Monster->GetMonsterStatInfo()->Direction = (m_Monster->m_Target->GetPos() - m_Monster->GetPos()).Normalize();

	// �ش� ��������, �ӷ¿� �°� �������Ӹ��� �̵�
	m_Monster->GetRigidBody()->SetVelocity(m_Monster->GetMonsterStatInfo()->Direction * m_Monster->GetMonsterStatInfo()->Speed);

	// ���� ���� �ð�ȭ
	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetPos(), m_Monster->GetMonsterStatInfo()->DetectRange);

}

void GMChaseState::Exit()
{
}


