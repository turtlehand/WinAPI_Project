#include "pch.h"
#include "GMonster.h"

#include "GAssetManager.h"
#include "GSound.h"

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

}

GMonster::~GMonster()
{

}

void GMonster::Dead()
{
	if (GetStatInfo()->IsDead)
		return;

	DropItem();
	GetStatInfo()->IsDead = true;
	//DeleteGameObject(this);

	m_FSM->ChanageState(L"DIE");
	m_RigidBody->SetVelocity(Vec2(0.f, 0.f));
}

void GMonster::Awake()
{
	GCreature::Awake();

	m_AttackBox = new GHitBox;
	m_AttackBox->Awake();
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(m_AttackBox, LAYER_TYPE::MONSTER_OBJECT);
	AddChild(m_AttackBox);

	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"ENEMY_DIE", L"FlipBook\\Enemy\\ENEMY_DIE.flip"));

	m_RigidBody = AddComponent<GRigidBody>();

	m_FSM = AddComponent<GFSM>();

}

const wstring& GMonster::GetCurrentState()
{
	return m_FSM->GetCurrentState();
}
