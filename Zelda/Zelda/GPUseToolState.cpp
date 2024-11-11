#include "pch.h"
#include "GPUseToolState.h"

#include "GAssetManager.h"

#include "GPlayer.h"
#include "GHitBox.h"
#include "GBoxCollider.h"
#include "GArrow.h"

#include "GFlipBookPlayer.h"


GPUseToolState::GPUseToolState() :
	m_Player(nullptr),
	m_PlayerInfo(nullptr),
	m_PrevAnim(PLAYER_ANIM_STATE::NONE)
{
}

GPUseToolState::~GPUseToolState()
{
}

void GPUseToolState::Begin()
{
	if (m_Player == nullptr)
	{
		m_Player = dynamic_cast<GPlayer*>(GetOwnerObj());
		assert(m_Player != nullptr);
	}

	if (m_PlayerInfo == nullptr)
	{
		m_PlayerInfo = m_Player->GetPlayerStatInfo();
	}

}

void GPUseToolState::Enter()
{
	m_PrevAnim = (PLAYER_ANIM_STATE)m_Player->m_FlipBookPlayer->GetCurIndex();

	if (m_PlayerInfo->Direction == Vec2::up())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_UP, 4.f, false);
	}
	else if (m_PlayerInfo->Direction == Vec2::down())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_DOWN, 4.f, false);
	}
	else if (m_PlayerInfo->Direction == Vec2::left())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 4.f, false);
		m_Player->m_FlipBookPlayer->SetXFlip(true);
	}
	else if (m_PlayerInfo->Direction == Vec2::right())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 4.f, false);
		m_Player->m_FlipBookPlayer->SetXFlip(false);
	}

	Bow();

	m_Player->m_FlipBookPlayer->Reset();
	m_Player->m_FlipBookPlayer->Play();
}

void GPUseToolState::FinalTick()
{
	if (m_Player->m_FlipBookPlayer->IsFinish())
	{
		m_Player->m_FSM->ChanageState(L"IDLE");
	}
}

void GPUseToolState::Exit()
{
	m_Player->m_FlipBookPlayer->SetPlay((int)m_PrevAnim, 5, true);
}

void GPUseToolState::Bow()
{
	GArrow* pArrow = new GArrow();
	pArrow->SetDamage(2);
	if (m_PlayerInfo->Direction == Vec2::up())
	{
		pArrow->SetPos(m_Player->GetPos() + Vec2(0.f, 32.f));
		pArrow->SetVelocity(Vec2::up() * 100.f);
	}
	else if (m_PlayerInfo->Direction == Vec2::down())
	{
		pArrow->SetPos(m_Player->GetPos() + Vec2(0.f, -32.f));
		pArrow->SetVelocity(Vec2::down() * 100.f);
	}
	else if (m_PlayerInfo->Direction == Vec2::left())
	{
		pArrow->SetPos(m_Player->GetPos() + Vec2(-32.f, 0.f));
		pArrow->SetVelocity(Vec2::left() * 100.f);
	}
	else if (m_PlayerInfo->Direction == Vec2::right())
	{
		pArrow->SetPos(m_Player->GetPos() + Vec2(32.f, 0.f));
		pArrow->SetVelocity(Vec2::right() * 100.f);

	}

	CreateGameObject(pArrow, LAYER_TYPE::PLAYER_OBJECT);
}