#include "pch.h"
#include "GMonster.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "GHitBox.h"

#include "GBoxCollider.h"
#include "GRigidBody.h"
#include "GFSM.h"
#include "GFlipBookPlayer.h"


GMonster::GMonster() :
	m_Target(nullptr),
	m_FSM(nullptr),
	m_HitBox(nullptr),
	m_FlipBookPlayer(nullptr),
	m_RigidBody(nullptr),
	m_AttackBox(nullptr)
{

	m_AttackBox = new GHitBox;
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(m_AttackBox, LAYER_TYPE::MONSTER_OBJECT);
	AddChild(m_AttackBox);

	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();

	m_HitBox = AddComponent<GBoxCollider>();

	m_RigidBody = AddComponent<GRigidBody>();

	m_FSM = AddComponent<GFSM>();
}

GMonster::~GMonster()
{
}

void GMonster::EnterOverlap(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction(HitBox);
}


const wstring& GMonster::GetCurrentState()
{
	return m_FSM->GetCurrentState();
}
