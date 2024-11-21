#include "pch.h"
#include "GPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "GAssetManager.h"
#include "GPathManager.h"

#include "GHitBox.h"

#include "GTexture.h"
#include "GFlipBook.h"
#include "GSprite.h"
#include "GSound.h"

#include "GBoxCollider.h"
#include "GCircleCollider.h"
#include "GFlipBookPlayer.h"
#include "GSpriteRenderer.h"
#include "GRigidBody.h"
#include "GFSM.h"

#include "GPIdleState.h"
#include "GPMoveState.h"
#include "GPAttackState.h"
#include "GPUseToolState.h"
#include "GPBeAttackedState.h"
#include "GPPickUpState.h"
#include "GPDieState.h"

#include "GHeart.h"
#include "GInventory.h"
#include "GPrefabManager.h"

GPlayer::GPlayer() :
	GCreature(CREATURE_ID::Player),
	m_FSM(nullptr),
	m_FlipBookPlayer(nullptr),
	m_RigidBody(nullptr),
	m_AttackBox(nullptr),
	m_Inventory{},
	m_NearbyItem(nullptr),
	m_WeaponEquip(CREATURE_ID::END),
	m_ToolEquip(CREATURE_ID::END)
{
	SetName(L"Player");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"LINK_DOWN_0", L"Sprite\\Link_16\\LINK_DOWN_0.sprite"));
}

GPlayer::~GPlayer()
{
	
}

void GPlayer::Awake()
{
	GCreature::Awake();

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

	// 공격 박스 설정
	m_AttackBox = new GHitBox;
	m_AttackBox->Awake();
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(m_AttackBox, LAYER_TYPE::PLAYER_OBJECT);
	AddChild(m_AttackBox);
	m_AttackBox->SetActive(false);
	m_AttackBox->SetName(L"Player_AttackBox");
	m_AttackBox->SetPos(0.f, 0.f);
	m_AttackBox->SetScale(0, 0);

	// UI
	m_Inventory.reserve(MAX_SLOT);
	GInventory* pInven = new GInventory(m_Inventory);
	pInven->Awake();
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pInven, LAYER_TYPE::UI);
	m_InventoryUI = pInven;
	m_InventoryUI->SetPos(CEngine::GetInst()->GetResolution() - Vec2(224.f, 80.f) - Vec2(8.f, 8.f));
	m_InventoryUI->SetScale(Vec2(224.f, 80.f));

	GHeart* pHeart = new GHeart(*pInfo);
	pHeart->Awake();
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pHeart, LAYER_TYPE::UI);
	pHeart->SetPos(Vec2(8.f, 8.f));
	pHeart->SetScale(32.f, 32.f);

	// FSM 추가
	m_FSM = AddComponent<GFSM>();
	m_FSM->SetName(L"Player_FSM");

	// 히트박스 추가
	GetHitBox()->SetName(L"Player_Hit_Box");
	GetHitBox()->SetPos(Vec2(0, 0));
	GetHitBox()->SetScale(Vec2(50.f, 50.f));
	m_AttackBox->GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"WEAPON_X", L"FlipBook\\Link_16\\Weapon\\WEAPON_X.flip"));
	m_AttackBox->GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"WEAPON_Y", L"FlipBook\\Link_16\\Weapon\\WEAPON_Y.flip"));

	m_AttackBox->GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"BOW_X", L"FlipBook\\Link_16\\BOW\\BOW_X.flip"));
	m_AttackBox->GetFlipBookPlayer()->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"BOW_Y", L"FlipBook\\Link_16\\BOW\\BOW_Y.flip"));

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
	m_FSM->AddState(L"TOOL", new GPUseToolState);
	m_FSM->AddState(L"BEATTACKED", new GPBeAttackedState);
	m_FSM->AddState(L"PICKUP", new GPPickUpState);
	m_FSM->AddState(L"DIE", new GPDieState);
	m_FSM->ChanageState(L"IDLE");

	// 처음 시작할 때는 유저데이터 저장
	if (CLevelMgr::GetInst()->GetCurrentLevelType() == LEVEL_TYPE::STAGE0)
		SaveUserData();
	else
		LoadUserData();
	
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
}

void GPlayer::OnTrigger(GCollider* _Collider)
{
	GCreature::OnTrigger(_Collider);
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
	//GetPlayerStatInfo()->Speed /= 2;
}

void GPlayer::OnCollisionExit(GCollider* _Collider)
{
	//GetPlayerStatInfo()->Speed *= 2;
}

const wstring& GPlayer::GetCurrentState()
{
	return m_FSM->GetCurrentState();
}

void GPlayer::CreateAnimator()
{
	m_FlipBookPlayer->SetName(L"Player_FlipBookPlayer");
	//m_FlipBookPlayer->SetScale(Vec2(4.f, 4.f));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_DIE", L"FlipBook\\Link_16\\LINK_DIE.flip"));

	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_UP", L"FlipBook\\Link_16\\LINK_UP.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_DOWN", L"FlipBook\\Link_16\\LINK_DOWN.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_RIGHT", L"FlipBook\\Link_16\\LINK_RIGHT.flip"));

	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_UP", L"FlipBook\\Link_16\\Attack\\LINK_UP_ATTACK.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_DOWN", L"FlipBook\\Link_16\\Attack\\LINK_DOWN_ATTACK.flip"));
	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_ATTACK_RIGHT", L"FlipBook\\Link_16\\Attack\\LINK_RIGHT_ATTACK.flip"));

	m_FlipBookPlayer->AddFlipBook(GAssetManager::GetInst()->LoadFlipBook(L"LINK_PICK_UP", L"FlipBook\\Link_16\\LINK_PICK_UP.flip"));

	m_FlipBookPlayer->SetPlay((int)PLAYER_ANIM_STATE::DOWN, 5, true);

	//m_FlipBookPlayer->SetDeleteColor(RGB(116, 116, 116));
}

void GPlayer::SetAttackBox(CREATURE_ID _WeaponID)
{
	GSprite* SpriteX = nullptr;
	GSprite* SpriteY = nullptr;

	assert((int)CREATURE_ID::WEAPON < (int)_WeaponID && (int)_WeaponID < (int)CREATURE_ID::TOOLS);
	m_WeaponEquip = _WeaponID;
	m_ToolEquip = CREATURE_ID::END;

	switch (_WeaponID)
	{
	case CREATURE_ID::Wooden_Sword:
	{
		m_AttackBox->SetAttackType(ATTACK_TYPE::SLASH);
		m_AttackBox->SetMaterialType(MATERIAL_TYPE::WOOD);
		m_AttackBox->SetDamage(2);
		SpriteX = GAssetManager::GetInst()->LoadSprite(L"WOODEN_SWORD_X", L"Sprite\\Item_16\\Weapon\\WOODEN_SWORD_X.sprite");
		SpriteY = GAssetManager::GetInst()->LoadSprite(L"WOODEN_SWORD_Y", L"Sprite\\Item_16\\Weapon\\WOODEN_SWORD_Y.sprite");
	}
	break;
	case CREATURE_ID::Iron_Sword:
	{
		m_AttackBox->SetAttackType(ATTACK_TYPE::SLASH);
		m_AttackBox->SetMaterialType(MATERIAL_TYPE::METAL);
		m_AttackBox->SetDamage(3);
		SpriteX = GAssetManager::GetInst()->LoadSprite(L"METAL_SWORD_X", L"Sprite\\Item_16\\Weapon\\METAL_SWORD_X.sprite");
		SpriteY = GAssetManager::GetInst()->LoadSprite(L"METAL_SWORD_Y", L"Sprite\\Item_16\\Weapon\\METAL_SWORD_Y.sprite");
	}
	break;
	case CREATURE_ID::Stone_Hammer:
	{
		m_AttackBox->SetAttackType(ATTACK_TYPE::STRIKE);
		m_AttackBox->SetMaterialType(MATERIAL_TYPE::STONE);
		m_AttackBox->SetDamage(4);
		SpriteX = GAssetManager::GetInst()->LoadSprite(L"STONE_HAMMER_X", L"Sprite\\Item_16\\Weapon\\STONE_HAMMER_X.sprite");
		SpriteY = GAssetManager::GetInst()->LoadSprite(L"STONE_HAMMER_Y", L"Sprite\\Item_16\\Weapon\\STONE_HAMMER_Y.sprite");
	}
	break;
	case CREATURE_ID::Iron_Hammer:
	{

	}
	break;
	case CREATURE_ID::Wooden_Spear:
	{

	}
	break;
	case CREATURE_ID::Iron_Spear:
	{

	}
	break;
	case CREATURE_ID::Korok_Leaf:
	{

	}
	break;
	case CREATURE_ID::Branch:
	{
		m_AttackBox->SetAttackType(ATTACK_TYPE::STRIKE);
		m_AttackBox->SetMaterialType(MATERIAL_TYPE::WOOD);
		m_AttackBox->SetDamage(1);
		SpriteX = GAssetManager::GetInst()->LoadSprite(L"BRANCH_X", L"Sprite\\Item_16\\Weapon\\BRANCH_X.sprite");
		SpriteY = GAssetManager::GetInst()->LoadSprite(L"BRANCH_Y", L"Sprite\\Item_16\\Weapon\\BRANCH_Y.sprite");
	}
	}


	m_AttackBox->GetSpriteRenderer()->SetSprite(nullptr);

	GFlipBook* AttackX = GAssetManager::GetInst()->FindFlipBook(L"WEAPON_X");

	// X 무기 스프라이트 변경
	for (size_t i = 0; i < 3; ++i)
	{
		AttackX->ChangeSprite(i, SpriteX);
	}

	GFlipBook* AttackY = GAssetManager::GetInst()->FindFlipBook(L"WEAPON_Y");

	// Y 무기 스프라이트 변경
	for (size_t i = 0; i < 3; ++i)
	{
		AttackY->ChangeSprite(i, SpriteY);
	}
	
	m_AttackBox->DeleteElement();

}

void GPlayer::SetTool(CREATURE_ID _ToolID)
{
	assert((int)CREATURE_ID::TOOLS < (int)_ToolID && (int)_ToolID < (int)CREATURE_ID::ETC);
	m_WeaponEquip = CREATURE_ID::END;
	m_ToolEquip = _ToolID;

	GetPlayerStatInfo()->AttackPower = 1;

	m_AttackBox->GetFlipBookPlayer()->SetPlay(-1, 0, 0);

	m_AttackBox->DeleteElement();
		
}

int GPlayer::SaveUserData()
{
	wstring RelativePath = GPathManager::GetContentPath();
	RelativePath += L"SaveData\\UserData.save";

	FILE* File = nullptr;
	_wfopen_s(&File, RelativePath.c_str(), L"w");
	assert(File);

	fwprintf_s(File, L"[MAXHP]\n");
	fwprintf_s(File, L"%d\n\n", GetPlayerStatInfo()->MaxHP);

	fwprintf_s(File, L"[HP]\n");
	fwprintf_s(File, L"%d\n\n", GetPlayerStatInfo()->HP);

	fwprintf_s(File, L"[ITEM]\n");

	for (int i = 0; i < m_Inventory.size(); ++i)
	{
		fwprintf_s(File, L"[INDEX]\n");
		fwprintf_s(File, L"%d\n\n", i);

		fwprintf_s(File, L"[CREATUREID]\n");
		fwprintf_s(File, L"%d\n\n", (int)m_Inventory[i].first);

		fwprintf_s(File, L"[NUM]\n");
		fwprintf_s(File, L"%d\n\n", (int)m_Inventory[i].second);
	}

	fclose(File);
	return S_OK;
}

int GPlayer::LoadUserData()
{
	wstring RelativePath = GPathManager::GetContentPath();
	RelativePath += L"SaveData\\UserData.save";

	FILE* File = nullptr;
	_wfopen_s(&File, RelativePath.c_str(), L"r");
	assert(File);

	while (true)
	{
		wchar_t szBuff[255] = {};
		fwscanf_s(File, L"%s", szBuff, 255);
		wstring szString = szBuff;
		if (szString.empty())
		{
			break;
		}


		if (szString == L"[MAXHP]")
		{
			int MaxHP = 0;
			fwscanf_s(File, L"%d", &MaxHP);
			GetPlayerStatInfo()->MaxHP = MaxHP;
		}
		else if (szString == L"[HP]")
		{
			int HP = 0;
			fwscanf_s(File, L"%d", &HP);
			GetPlayerStatInfo()->HP = HP;
		}
		else if (szString == L"[INDEX]")
		{
			int index = 0;
			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &index);

			int ItemID, Num;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &ItemID);

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &Num);
			
			m_Inventory.push_back(make_pair((CREATURE_ID)ItemID, Num));
		}

	}

	m_InventoryUI->SetCurItem(m_InventoryUI->FristItem());

	fclose(File);

	return S_OK;
}

void GPlayer::Dead()
{
	if (GetStatInfo()->IsDead)
		return;

	DropItem();
	GetStatInfo()->IsDead = true;
	//DeleteGameObject(this);

	m_FSM->ChanageState(L"DIE");
	m_RigidBody->SetVelocity(Vec2(0.f, 0.f));
}

#pragma region Item

void GPlayer::PickUpItem()
{
	// 근처 아이템이 없거나 슬롯이 꽉찼다면
	if (!IsValid(m_NearbyItem) || m_Inventory.size() == MAX_SLOT)
		return;

	// 이 오브젝트가 아이템인지 확인한다.
	GItem* Item = dynamic_cast<GItem*>(m_NearbyItem);
	assert(Item != nullptr);

	vector<pair<CREATURE_ID, int>>::iterator iter = m_Inventory.begin();

	// 인벤토리에서 아이템이 있는지 찾는다.
	for (iter; iter != m_Inventory.end(); ++iter)
	{
		if (iter->first == Item->GetCreatureID())
			break;
	}


	// 인벤토리에서 아이템을 못 찾았다.
	if (iter == m_Inventory.end())
	{
		// 인벤토리에서 아이템을 추가한다.
		m_Inventory.push_back(make_pair(Item->GetCreatureID(), 1));
		m_InventoryUI->SetCurItem(m_InventoryUI->LastItem());
		m_FSM->ChanageState(L"PICKUP");
	}
	// 인벤토리에서 아이템을 찾았다.
	else
	{
		GAssetManager::GetInst()->LoadSound(L"Pick_Up", L"Sound\\Sound_Effects\\LOZ_Get_Item.wav")->Play();
		//아이템 수를 증가시킨다.
		++((*iter).second);
	}

	DeleteGameObject((CObj*)(m_NearbyItem));
	m_NearbyItem = nullptr;

}

void GPlayer::DropInvenItem()
{
	// 아이템이 없다면 반환
	if (m_Inventory.size() == 0)
		return;

	m_InventoryUI->DropItem(this);
	GSound* DropSound = GAssetManager::GetInst()->LoadSound(L"Drop", L"Sound\\Sound_Effects\\LOZ_Bomb_Drop.wav");
	DropSound->SetVolume(100.f);
	DropSound->Play();

}

void GPlayer::UseItem()
{
	// 아이템이 없다면 반환
	if (m_Inventory.size() == 0)
		return;

	m_InventoryUI->UseItem(this);
}


#pragma endregion


