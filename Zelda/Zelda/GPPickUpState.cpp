#include "pch.h"
#include "GPPickUpState.h"

#include "GPlayer.h"
#include "GInventory.h"

#include "GFlipBookPlayer.h"

#include "GAssetManager.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "GSound.h"

#include "GPanel.h"
#include "GGameImage.h"



GPPickUpState::GPPickUpState() :
	m_PickUpSound(nullptr),
	m_Player(nullptr)
{
}

GPPickUpState::~GPPickUpState()
{
}

void GPPickUpState::Awake()
{

	if (m_Player == nullptr)
	{
		m_Player = dynamic_cast<GPlayer*>(GetOwnerObj());
		assert(m_Player != nullptr);
	}

	m_PickUpSound = GAssetManager::GetInst()->LoadSound(L"Pick_Up", L"Sound\\Sound_Effects\\LOZ_Get_Item.wav");
	m_PickUpSound->SetVolume(100.f);

	m_ItemImage = new GGameImage;
	m_ItemImage->Awake();
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(m_ItemImage, LAYER_TYPE::UI);
	m_ItemImage->SetActive(false);
	m_ItemImage->SetScale(64.f, 64.f);
}

void GPPickUpState::Enter()
{
	m_PrevAnim = (PLAYER_ANIM_STATE)m_Player->m_FlipBookPlayer->GetCurIndex();

	m_Player->m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::PICK_UP, 3, false);
	m_Player->GetStatInfo()->IsInvincible = true;

	m_PickUpSound->Play();

	m_ItemImage->SetPos(m_Player->GetGlobalPos() + Vec2::up() * 80.f);
	m_ItemImage->SetSprite(m_Player->m_InventoryUI->GetCurItemSprite());
	m_ItemImage->SetActive(true);
}

void GPPickUpState::FinalTick()
{
	m_ItemImage->SetPos(m_Player->GetGlobalPos() + Vec2::up() * 80.f);
	if (m_Player->m_FlipBookPlayer->IsFinish())
		m_Player->m_FSM->ChanageState(L"IDLE");
}

void GPPickUpState::Exit()
{
	m_ItemImage->SetActive(false);
	m_Player->GetStatInfo()->IsInvincible = false;
	m_Player->m_FlipBookPlayer->SetPlay((int)m_PrevAnim, 5, true);
}