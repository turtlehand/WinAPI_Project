#include "pch.h"
#include "GMoblin.h"

#include "GHitBox.h"


#include "GAssetManager.h"

#include "GBoxCollider.h"
#include "GRigidBody.h"
#include "GFSM.h"
#include "GFlipBookPlayer.h"

#include "GMIdleState.h"
#include "GMChaseState.h"
#include "GMBeAttackedState.h"

GMoblin::GMoblin() :
	GMonster(CREATURE_ID::Moblin)
{
	SetName(L"Moblin");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"MOBLIN_DOWN", L"Sprite\\Overworld_Enemies\\MOBLIN_DOWN.sprite"));
}

GMoblin::~GMoblin()
{
}

void GMoblin::Awake()
{
	GMonster::Awake();

	MonsterInfo* pMInfo = new MonsterInfo;
	pMInfo->Material = MATERIAL_TYPE::LIFE;
	pMInfo->MaxHP = 12;
	pMInfo->HP = 12;
	pMInfo->AttackPower = 4;
	pMInfo->Speed = 64;
	pMInfo->Direction = Vec2::down();
	pMInfo->DetectRange = 128;
	pMInfo->DetectKeepRange = 256;
	pMInfo->AttackRange = 0;
	pMInfo->IsDead = false;
	SetStatInfo(pMInfo);

	GetHitBox()->SetName(L"Moblin_HitBox");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));

	GetAttackBox()->SetName(L"Moblin_AttackBox");

	GetRigidBody()->SetName(L"Moblin_RigidBody");
	GetRigidBody()->SetMass(1.f);
	GetRigidBody()->SetFriction(900.f);

	GetFSM()->SetName(L"Moblin_FSM");
	CreateAnimator();

	GetAttackBox()->GetComponent<GBoxCollider>()->SetScale(Vec2(64.f, 64.f));
	GetAttackBox()->SetAttackType(ATTACK_TYPE::STRIKE);
	GetAttackBox()->SetMaterialType(MATERIAL_TYPE::LIFE);
	GetAttackBox()->SetDamage(1);

	GetFSM()->AddState(L"IDLE", new GMIdleState);
	GetFSM()->AddState(L"CHASE", new GMChaseState);
	GetFSM()->AddState(L"BEATTACKED", new GMBeAttackedState);
	GetFSM()->ChanageState(L"IDLE");
}

void GMoblin::Tick()
{
	GCreature::Tick();
}

void GMoblin::Render()
{
	GetFlipBookPlayer()->Render();
}

void GMoblin::CreateAnimator()
{
	GetFlipBookPlayer()->SetName(L"Moblin_FlipBookPlayer");
	//GetFlipBookPlayer()->SetScale(Vec2(4.f, 4.f));

	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"MOBLIN_UP", L"FlipBook\\Moblin_16\\MOBLIN_UP.flip"));
	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"MOBLIN_DOWN", L"FlipBook\\Moblin_16\\MOBLIN_DOWN.flip"));
	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"MOBLIN_RIGHT", L"FlipBook\\Moblin_16\\MOBLIN_RIGHT.flip"));

	GetFlipBookPlayer()->SetPlay((int)MOBLIN_ANIM_STATE::DOWN, 5, true);

	//GetFlipBookPlayer()->SetDeleteColor(RGB(116, 116, 116));
}

