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
	// ���� ����� ���ٸ� ���¸� �ٲ۴�.
	if (!IsValid(m_Monster->m_Target))
		m_Monster->m_FSM->ChanageState(L"IDLE");

	// ������ �̵��ӵ��� �°Ԥ� �÷��̾ ���ؼ� �̵��Ѵ�.
	m_Monster->m_Dir = (m_Monster->m_Target->GetPos() - m_Monster->GetPos()).Normalize();

	// �ش� ��������, �Ӥ��¿� �°� �������Ӹ��� �̵�
	Vec2 vPos = m_Monster->GetPos()+  m_Monster->m_Dir * m_Monster->GetInfo().Speed * DT;
	m_Monster->SetPos(vPos);

	// ���� ���� �ð�ȭ
	DrawDebugCircle(PEN_TYPE::GREEN, 0.f, m_Monster->GetPos(), m_Monster->GetInfo().DetectRange);

}

void GMChaseState::Exit()
{
}


