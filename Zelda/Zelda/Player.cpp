#include "pch.h"
#include "Player.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "TaskManager.h"
#include "DeBugRenderManager.h"
#include "GAssetManager.h"
#include "GPathManager.h"
#include "GCamera.h"

#include "CLevel.h"
#include "CSelectGDI.h"

#include "Missile.h"
#include "GuidedMissile.h"

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

Player::Player() :
	m_FSM(nullptr),
	m_Collider(nullptr),
	m_FlipBookPlayer(nullptr),
	m_RigidBody(nullptr)
{

	CreateAnimator();

	m_FSM = AddComponent<GFSM>();
	m_FSM->SetName(L"Player_FSM");
	m_FSM->AddState(L"MOVE", new GPMoveState);
	m_FSM->AddState(L"IDLE", new GPIdleState);
	m_FSM->AddState(L"ATTACK", new GPAttackState);
	m_FSM->ChanageState(L"IDLE");

	m_Collider = AddComponent<GCircleCollider>();
	m_Collider->SetName(L"Player_Hit_Box");
	m_Collider->SetPos(Vec2(0, 0));
	m_Collider->SetRadius(64.f);
	m_Collider->GetID();

	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetName(L"Player_RigidBody");
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(900.f);

	
}

Player::~Player()
{

}


void Player::Begin()
{

}

void Player::Tick()
{

}


void Player::Render()
{
	m_FlipBookPlayer->Render();
}

const wstring& Player::GetCurrentState()
{
	return m_FSM->GetCurrentState();
	// TODO: 여기에 return 문을 삽입합니다.
}

void Player::CreateAnimator()
{
	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();
	m_FlipBookPlayer->SetName(L"Player_FlipBookPlayer");
	m_FlipBookPlayer->SetScale(Vec2(4.f, 4.f));

	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_UP", L"FlipBook\\Link_16\\LINK_UP.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_DOWN", L"FlipBook\\Link_16\\LINK_DOWN.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_RIGHT", L"FlipBook\\Link_16\\LINK_RIGHT.flip"));

	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_UP", L"FlipBook\\Link_16\\Wooden_Sword\\LINK_UP_WOODEN_SWORD.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_DOWN", L"FlipBook\\Link_16\\Wooden_Sword\\LINK_DOWN_WOODEN_SWORD.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_RIGHT", L"FlipBook\\Link_16\\Wooden_Sword\\LINK_RIGHT_WOODEN_SWORD.flip"));


	m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::DOWN, 5, true);

	m_FlipBookPlayer->SetDeleteColor(RGB(116, 116, 116));
}
