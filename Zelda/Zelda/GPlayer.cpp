#include "pch.h"
#include "GPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "GAssetManager.h"

#include "GHitBox.h"

#include "GTexture.h"
#include "GFlipBook.h"
#include "GSprite.h"

#include "GBoxCollider.h"
#include "GCircleCollider.h"
#include "GFlipBookPlayer.h"
#include "GRigidBody.h"
#include "GFSM.h"

#include "GPIdleState.h"
#include "GPMoveState.h"
#include "GPAttackState.h"

GPlayer::GPlayer() :
	m_FSM(nullptr),
	m_Collider(nullptr),
	m_FlipBookPlayer(nullptr),
	m_RigidBody(nullptr),
	m_AttackBox(nullptr)
{
	SetName(L"Player");

	// 공격 박스 설정
	m_AttackBox = new GHitBox;
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(m_AttackBox, LAYER_TYPE::PLAYER_OBJECT);
	AddChild(m_AttackBox);
	m_AttackBox->SetActive(false);
	m_AttackBox->SetName(L"Player_AttackBox");
	m_AttackBox->SetPos(0.f, 0.f);
	m_AttackBox->SetScale(0, 0);

	// 스탯 설정
	PlayerInfo* pInfo = new PlayerInfo;
	pInfo->Material = MATERIAL_TYPE::LIFE;
	pInfo->MaxHP = 12;
	pInfo->HP = 12;
	pInfo->AttackPower = 0;
	pInfo->Speed = 128;
	pInfo->Direction = Vec2::down();
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	// FSM 추가
	m_FSM = AddComponent<GFSM>();
	m_FSM->SetName(L"Player_FSM");

	// 히트박스 추가
	m_Collider = AddComponent<GBoxCollider>();
	m_Collider->SetName(L"Player_Hit_Box");
	m_Collider->SetPos(Vec2(0, 0));
	m_Collider->SetScale(Vec2(64.f, 64.f));

	// 강체 추가
	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetName(L"Player_RigidBody");
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(900.f);

	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();
	CreateAnimator();

	m_FSM->AddState(L"MOVE", new GPMoveState);
	m_FSM->AddState(L"IDLE", new GPIdleState);
	m_FSM->AddState(L"ATTACK", new GPAttackState);
	m_FSM->ChanageState(L"IDLE");
}

GPlayer::~GPlayer()
{

}

void GPlayer::Begin()
{
	

}

void GPlayer::Tick()
{
	GCreature::Tick();
}


void GPlayer::Render()
{
	m_FlipBookPlayer->Render();
	RenderEffect();
}

void GPlayer::OnTriggerEnter(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction(HitBox);
}

void GPlayer::OnCollisionEnter(GCollider* _Collider)
{
	GetPlayerStatInfo()->Speed /= 2;
}

void GPlayer::OnCollisionExit(GCollider* _Collider)
{
	GetPlayerStatInfo()->Speed *= 2;
}

const wstring& GPlayer::GetCurrentState()
{
	return m_FSM->GetCurrentState();
}

void GPlayer::CreateAnimator()
{
	m_FlipBookPlayer->SetName(L"Player_FlipBookPlayer");
	//m_FlipBookPlayer->SetScale(Vec2(4.f, 4.f));

	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_UP", L"FlipBook\\Link_16\\LINK_UP.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_DOWN", L"FlipBook\\Link_16\\LINK_DOWN.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_RIGHT", L"FlipBook\\Link_16\\LINK_RIGHT.flip"));

	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_UP", L"FlipBook\\Link_16\\Attack\\LINK_UP_ATTACK.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_DOWN", L"FlipBook\\Link_16\\Attack\\LINK_DOWN_ATTACK.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_RIGHT", L"FlipBook\\Link_16\\Attack\\LINK_RIGHT_ATTACK.flip"));


	m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::DOWN, 5, true);

	//m_FlipBookPlayer->SetDeleteColor(RGB(116, 116, 116));
}
