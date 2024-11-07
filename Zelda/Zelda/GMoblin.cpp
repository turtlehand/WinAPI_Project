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

GMoblin::GMoblin()
{
	SetName(L"Moblin");

	MonsterInfo* pMInfo = new MonsterInfo;
	pMInfo->Material = MATERIAL_TYPE::LIFE;
	pMInfo->MaxHP = 4;
	pMInfo->HP = 4;
	pMInfo->AttackPower = 4;
	pMInfo->Speed = 64;
	pMInfo->Direction = Vec2::down();
	pMInfo->DetectRange = 256;
	pMInfo->AttackRange = 0;
	pMInfo->IsDead = false;
	SetStatInfo(pMInfo);

	GetHitBox()->SetName(L"Moblin_HitBox");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));

	GetRigidBody()->SetName(L"Moblin_RigidBody");
	GetRigidBody()->SetMass(1.f);
	GetRigidBody()->SetFriction(900.f);

	GetFSM()->SetName(L"Moblin_FSM");
	CreateAnimator();

	GetAttackBox()->GetComponent<GBoxCollider>()->SetScale(Vec2(64.f, 64.f));
	GetAttackBox()->SetAttackType(ATTACK_TYPE::STRIKE);
	GetAttackBox()->SetMaterialType(MATERIAL_TYPE::LIFE);
	GetAttackBox()->SetDamage(4);

	GetFSM()->AddState(L"IDLE", new GMIdleState);
	GetFSM()->AddState(L"CHASE", new GMChaseState);
	GetFSM()->ChanageState(L"IDLE");
}

GMoblin::~GMoblin()
{
}

void GMoblin::Begin()
{
	
}

void GMoblin::Tick()
{
	GCreature::Tick();
}

void GMoblin::Render()
{
	GetFlipBookPlayer()->Render();
	RenderEffect();
}

void GMoblin::CreateAnimator()
{
	GetFlipBookPlayer()->SetName(L"Moblin_FlipBookPlayer");
	GetFlipBookPlayer()->SetScale(Vec2(4.f, 4.f));

	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"MOBLIN_UP", L"FlipBook\\Moblin_16\\MOBLIN_UP.flip"));
	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"MOBLIN_DOWN", L"FlipBook\\Moblin_16\\MOBLIN_DOWN.flip"));
	GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"MOBLIN_RIGHT", L"FlipBook\\Moblin_16\\MOBLIN_RIGHT.flip"));

	GetFlipBookPlayer()->SetPlay((int)MOBLIN_ANIM_STATE::DOWN, 5, true);

	GetFlipBookPlayer()->SetDeleteColor(RGB(116, 116, 116));
}

