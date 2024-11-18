#include "pch.h"
#include "GPUseToolState.h"

#include "GAssetManager.h"

#include "GPlayer.h"
#include "GHitBox.h"
#include "GBoxCollider.h"
#include "GArrow.h"

#include "GFlipBookPlayer.h"
#include "GSpriteRenderer.h"


GPUseToolState::GPUseToolState() :
	m_Player(nullptr),
	m_PlayerInfo(nullptr),
	m_AttackBox(nullptr),
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

	if (m_AttackBox == nullptr)
	{
		m_AttackBox = m_Player->m_AttackBox;
	}

}

void GPUseToolState::Enter()
{
	m_PrevAnim = (PLAYER_ANIM_STATE)m_Player->m_FlipBookPlayer->GetCurIndex();


	if (m_PlayerInfo->Direction == Vec2::up())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_UP, 30.f, false);
	}
	else if (m_PlayerInfo->Direction == Vec2::down())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_DOWN, 30.f, false);
	}
	else if (m_PlayerInfo->Direction == Vec2::left())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 30.f, false);
		m_Player->m_FlipBookPlayer->SetXFlip(true);
	}
	else if (m_PlayerInfo->Direction == Vec2::right())
	{
		m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::ATTACK_RIGHT, 30.f, false);
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
	m_Player->m_AttackBox->SetActive(false);
	m_Player->m_FlipBookPlayer->SetPlay((int)m_PrevAnim, 5, true);
}

void GPUseToolState::Bow()
{
	GArrow* pArrow = new GArrow();
	CreateGameObject(pArrow, LAYER_TYPE::PLAYER_OBJECT);
	pArrow->SetDamage(m_PlayerInfo->AttackPower);

	m_AttackBox->SetDamage(0);
	m_AttackBox->SetMaterialType(MATERIAL_TYPE::NONE);
	m_AttackBox->SetAttackType(ATTACK_TYPE::NONE);
	m_AttackBox->SetActive(true);

	if (m_PlayerInfo->Direction == Vec2::up())
	{
		m_AttackBox->SetPos(0.f, 32.f);
		m_AttackBox->GetFlipBookPlayer()->SetPlay((int)ATTACK_ANIM_STATE::BOW_X, 4, false);
		m_AttackBox->GetFlipBookPlayer()->SetYFlip(false);

		pArrow->SetPos(m_Player->GetPos() + Vec2(0.f, 32.f));
		pArrow->SetVelocity(Vec2::up() * 1024.f);
	}
	else if (m_PlayerInfo->Direction == Vec2::down())
	{
		m_AttackBox->SetPos(0.f, -32.f);
		m_AttackBox->GetFlipBookPlayer()->SetPlay((int)ATTACK_ANIM_STATE::BOW_X, 4, false);
		m_AttackBox->GetFlipBookPlayer()->SetYFlip(true);

		pArrow->SetPos(m_Player->GetPos() + Vec2(0.f, -32.f));
		pArrow->SetVelocity(Vec2::down() * 1024.f);
	}
	else if (m_PlayerInfo->Direction == Vec2::left())
	{
		m_AttackBox->SetPos(-32.f,0.f);
		m_AttackBox->GetFlipBookPlayer()->SetPlay((int)ATTACK_ANIM_STATE::BOW_Y, 4, false);
		m_AttackBox->GetFlipBookPlayer()->SetXFlip(true);

		pArrow->SetPos(m_Player->GetPos() + Vec2(-32.f, 0.f));
		pArrow->SetVelocity(Vec2::left() * 1024.f);
	}
	else if (m_PlayerInfo->Direction == Vec2::right())
	{
		m_AttackBox->SetPos(32.f, 0.f);
		m_AttackBox->GetFlipBookPlayer()->SetPlay((int)ATTACK_ANIM_STATE::BOW_Y, 4, false);
		m_AttackBox->GetFlipBookPlayer()->SetXFlip(false);

		pArrow->SetPos(m_Player->GetPos() + Vec2(32.f, 0.f));
		pArrow->SetVelocity(Vec2::right() * 1024.f);

	}

	
}