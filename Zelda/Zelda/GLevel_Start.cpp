#include "pch.h"
#include "GLevel_Start.h"

#include "CollisionManager.h"
#include "GCamera.h"

#include "GPlayer.h"
#include "GMonster.h"
#include "GMoblin.h"
#include "GPlatform.h"
#include "GHitBox.h"
#include "GRock.h"
#include "GTree.h"
#include "GPullRock.h"
#include "GGrass.h"

#include "GFireWood.h"
#include "GFlint.h"
#include "GFruit.h"
#include "GRoastFruit.h"
#include "GWeapon.h"
#include "GBow.h"

#include "GInventory.h"

#include "GPathManager.h"

#include "GMap.h"
#include "GTileMap.h"
#include "GAssetManager.h"
#include "GSound.h"

GLevel_Start::GLevel_Start() :
	m_Player(nullptr),
	m_Map(nullptr)
{
	SetName(L"Start");
}

GLevel_Start::~GLevel_Start()
{
}

void GLevel_Start::Begin()
{
	//GSound* pSound = GAssetManager::GetInst()->LoadSound(L"Start_Level", L"Sound\\BGM_Stage1.wav");

	//if (pSound != nullptr)
	//{
	//	pSound->SetVolume(1.f);
	//	pSound->PlayToBGM(true);
	//}

	//
	GInventory* pInven = new GInventory;
	pInven->Awake();
	AddObject(pInven, LAYER_TYPE::UI);


	// Player 持失馬奄
	GPlayer* player = new GPlayer;
	player->Awake();
	m_Player = player;
	player->SetInvenUI(pInven);
	AddObject(player, LAYER_TYPE::PLAYER);
	player->SetPos(0.f, 0.f);

	GCamera::GetInst()->SetTarget(player);

	/*
	GRock* pRock = new GRock;
	pRock->Awake();
	AddObject(pRock, LAYER_TYPE::OBJECT);
	pRock->SetPos(-300.f, 200.f);

	GTree* pTree = new GTree;
	pTree->Awake();
	AddObject(pTree, LAYER_TYPE::OBJECT);
	pTree->SetPos(-300.f, 100.f);

	GPullRock* pPullRock = new GPullRock;
	pPullRock->Awake();
	AddObject(pPullRock, LAYER_TYPE::OBJECT);
	pPullRock->SetPos(-300.f, 0.f);

	GGrass* pGrass = new GGrass;
	pGrass->Awake();
	AddObject(pGrass, LAYER_TYPE::OBJECT);
	pGrass->SetPos(-300.f, - 100.f);

	GFireWood* pFireWood = new GFireWood;
	pFireWood->Awake();
	AddObject(pFireWood, LAYER_TYPE::ITEM);
	pFireWood->SetPos(-300.f, -200.f);

	GFlint* pFlint = new GFlint;
	pFlint->Awake();
	AddObject(pFlint, LAYER_TYPE::ITEM);
	pFlint->SetPos( -100.f, 0.f);

	// Monster 持失馬奄
	GMoblin* pMoblin = new GMoblin;
	pMoblin->Awake();
	AddObject(pMoblin, LAYER_TYPE::MONSTER);
	pMoblin->SetPos(300.f, 200.f);
	
	
	GFruit* pFruit = new GFruit;
	pFruit->Awake();
	AddObject(pFruit, LAYER_TYPE::ITEM);
	pFruit->SetPos(300.f, 0.f);
	
	GWeapon* pWoodenSword = new GWeapon(CREATURE_ID::Wooden_Sword);
	pWoodenSword->Awake();
	AddObject(pWoodenSword, LAYER_TYPE::ITEM);
	pWoodenSword->SetPos(300.f, -100.f);

	GWeapon* pMetalSword = new GWeapon(CREATURE_ID::Iron_Sword);
	pMetalSword->Awake();
	AddObject(pMetalSword, LAYER_TYPE::ITEM);
	pMetalSword->SetPos(100.f, 0.f);

	GBow* pBow = new GBow;
	pBow->Awake();
	AddObject(pBow, LAYER_TYPE::ITEM);
	pBow->SetPos(300.f, -200.f);
	
	GWeapon* pStoneHammer = new GWeapon(CREATURE_ID::Stone_Hammer);
	pStoneHammer->Awake();
	AddObject(pStoneHammer, LAYER_TYPE::ITEM);
	pStoneHammer->SetPos(100.f, -100.f);

	*/

	
	
	GMap* pMap = new GMap;
	m_Map = pMap;
	pMap->Awake();
	AddObject(pMap, LAYER_TYPE::BACKGROUND);
	wstring pMapPath = GPathManager::GetContentPath();
	pMapPath += L"TileMap\\test_BigMap.tm";
	pMap->SetName(L"Map");
	pMap->SetPos(pMap->GetPos() - Vec2(TILE_SIZE * 4 * 5, TILE_SIZE * 4 * 5));
	pMap->GetTileMap()->SetScale(Vec2(4.f, 4.f));
	pMap->GetTileMap()->Load(pMapPath);
	
	pMap->SetActive(true);

	//GRoastFruit* pRoastFruit = new GRoastFruit;
	//AddObject(pRoastFruit, LAYER_TYPE::ITEM);
	//pRoastFruit->SetPos(300.f, 1.f);
	

	CollisionManager::GetInst()->CollisionCheckClear();
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::ITEM);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ITEM);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::OBJECT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::OBJECT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::OBJECT, LAYER_TYPE::ITEM);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::ELEMENT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::PLAYER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::PLAYER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::MONSTER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::ITEM);
}

void GLevel_Start::Tick()
{
	CLevel::Tick();
	

	if (GETKEYDOWN(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
	else if (GETKEYDOWN(KEY::NUM8))
	{
		m_Map->SetActive(!m_Map->GetActive());
	}
}

void GLevel_Start::Render()
{
	CLevel::Render();

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Start Level", wcslen(L"Start Level"));
	//TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, m_Player->GetCurrentState().c_str(), m_Player->GetCurrentState().size());
}
