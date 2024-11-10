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

#include "GFireWood.h"
#include "GFlint.h"

GPlayer::GPlayer() :
	m_FSM(nullptr),
	m_FlipBookPlayer(nullptr),
	m_RigidBody(nullptr),
	m_AttackBox(nullptr),
	m_Inventory{},
	m_NearbyItem(nullptr)
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
	GetHitBox()->SetName(L"Player_Hit_Box");
	GetHitBox()->SetPos(Vec2(0, 0));
	GetHitBox()->SetScale(Vec2(64.f, 64.f));

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

	m_Inventory.reserve(MAX_SLOT);
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

void GPlayer::OnTrigger(GCollider* _Collider)
{
	if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::ITEM)
	{
		m_NearbyItem = (GItem*)_Collider->GetOwner();
	}
}

void GPlayer::OnTriggerExit(GCollider* _Collider)
{
	if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::ITEM)
	{
		m_NearbyItem = nullptr;
	}
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

void GPlayer::PickUpItem()
{
	// 근처 아이템이 없거나 슬롯이 꽉찼다면
	if (!IsValid(m_NearbyItem) || m_Inventory.size() == MAX_SLOT)
		return;

	// 이 오브젝트가 아이템인지 확인한다.
	GItem* Item = dynamic_cast<GItem*>(m_NearbyItem);
	assert(Item != nullptr);

	vector<pair<ITEM_ID, int>>::iterator iter = m_Inventory.begin();

	// 인벤토리에서 아이템이 있는지 찾는다.
	for (iter ; iter != m_Inventory.end(); ++iter)
	{
		if (iter->first == Item->GetItemID())
			break;
	}


	// 인벤토리에서 아이템을 못 찾았다.
	if (iter == m_Inventory.end())
	{
		// 인벤토리에서 아이템을 추가한다.
		m_Inventory.push_back(make_pair(Item->GetItemID(), 1));
	}
	// 인벤토리에서 아이템을 찾았다.
	else 
	{
		//아이템 수를 증가시킨다.
		++((*iter).second);
	}
	DeleteGameObject((CObj*)(m_NearbyItem));
	m_NearbyItem = nullptr;
	
}

void GPlayer::DropItem(int index)
{
	//index가 현재 인벤토리보다 크다면 반환
	if (index >= m_Inventory.size())
		return;

	// 인벤토리의 아이템의 개수가 1 이상이어야 한다.
	assert(m_Inventory[index].second > 0);

	// 아이템을 생성한다.
	if (m_Inventory[index].first == ITEM_ID::Fire_Wood)
	{
		CObj* Fire_Wood = new GFireWood;
		Fire_Wood->SetPos(GetPos().x, GetPos().y);
		CreateGameObject(Fire_Wood, LAYER_TYPE::ITEM);
	}
	else if (m_Inventory[index].first == ITEM_ID::Flint)
	{
		CObj* Flint = new GFlint;
		Flint->SetPos(GetPos().x, GetPos().y);
		CreateGameObject(Flint, LAYER_TYPE::ITEM);
	}


	// 해당 인벤토리의 아이템의 개수가 1이라면 슬롯에서 지운다.
	if (m_Inventory[index].second == 1)
		m_Inventory.erase(m_Inventory.begin() + index);
	else
		m_Inventory[index].second -= 1;
		
}

void GPlayer::UseItem(int index)
{
	//index가 현재 인벤토리보다 크다면 반환
	if (index >= m_Inventory.size())
		return;

	// 인벤토리의 아이템의 개수가 1 이상이어야 한다.
	assert(m_Inventory[index].second > 0);

	// 음식일 때
	if (200 < (int)m_Inventory[index].first && (int)m_Inventory[index].first < 300)
	{
		
	}
	// 무기일 때

	// 도구일 때
}
