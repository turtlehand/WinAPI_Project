#include "pch.h"
#include "GMonster.h"

#include "CLevel.h"
#include "CLevelMgr.h"

#include "GHitBox.h"

#include "GBoxCollider.h"
#include "GRigidBody.h"
#include "GFSM.h"
#include "GFlipBookPlayer.h"


GMonster::GMonster(CREATURE_ID _CreatureID) :
	GCreature(_CreatureID),
	m_Target(nullptr),
	m_FSM(nullptr),
	m_FlipBookPlayer(nullptr),
	m_RigidBody(nullptr),
	m_AttackBox(nullptr)
{

	m_AttackBox = new GHitBox;
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(m_AttackBox, LAYER_TYPE::MONSTER_OBJECT);
	AddChild(m_AttackBox);

	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();

	m_RigidBody = AddComponent<GRigidBody>();

	m_FSM = AddComponent<GFSM>();
}

GMonster::~GMonster()
{
}



const wstring& GMonster::GetCurrentState()
{
	return m_FSM->GetCurrentState();
}
