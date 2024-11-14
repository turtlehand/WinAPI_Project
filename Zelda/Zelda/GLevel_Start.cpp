#include "pch.h"
#include "GLevel_Start.h"

#include "CollisionManager.h"

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
	m_Player(nullptr)
{
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
	AddObject(pInven, LAYER_TYPE::UI);


	// Player 持失馬奄
	GPlayer* player = new GPlayer;
	m_Player = player;
	player->SetInvenUI(pInven);
	AddObject(player, LAYER_TYPE::PLAYER);
	player->SetPos(0.f, 0.f);

	GRock* pRock = new GRock;
	AddObject(pRock, LAYER_TYPE::OBJECT);
	pRock->SetPos(-300.f, 200.f);

	GTree* pTree = new GTree;
	AddObject(pTree, LAYER_TYPE::OBJECT);
	pTree->SetPos(-300.f, 100.f);

	GPullRock* pPullRock = new GPullRock;
	AddObject(pPullRock, LAYER_TYPE::OBJECT);
	pPullRock->SetPos(-300.f, 0.f);

	GGrass* pGrass = new GGrass;
	AddObject(pGrass, LAYER_TYPE::OBJECT);
	pGrass->SetPos(-300.f, - 100.f);

	GFireWood* pFireWood = new GFireWood;
	AddObject(pFireWood, LAYER_TYPE::ITEM);
	pFireWood->SetPos(-300.f, -200.f);

	GFlint* pFlint = new GFlint;
	AddObject(pFlint, LAYER_TYPE::ITEM);
	pFlint->SetPos( -100.f, 0.f);

	// Monster 持失馬奄
	GMoblin* pMoblin = new GMoblin;
	AddObject(pMoblin, LAYER_TYPE::MONSTER);
	pMoblin->SetPos(300.f, 200.f);
	
	GFruit* pFruit = new GFruit;
	AddObject(pFruit, LAYER_TYPE::ITEM);
	pFruit->SetPos(300.f, 0.f);

	GWeapon* pWoodenSword = new GWeapon(CREATURE_ID::Wooden_Sword);
	AddObject(pWoodenSword, LAYER_TYPE::ITEM);
	pWoodenSword->SetPos(300.f, -100.f);

	GWeapon* pMetalSword = new GWeapon(CREATURE_ID::Iron_Sword);
	AddObject(pMetalSword, LAYER_TYPE::ITEM);
	pMetalSword->SetPos(100.f, 0.f);

	GBow* pBow = new GBow;
	AddObject(pBow, LAYER_TYPE::ITEM);
	pBow->SetPos(300.f, -200.f);

	//GMap* pMap = new GMap;
	//m_Map = pMap;
	//AddObject(pMap, LAYER_TYPE::TILE);
	//wstring pMapPath = GPathManager::GetContentPath();
	//pMapPath += L"TileMap\\test_Creature.tm";
	//pMap->SetName(L"Map");
	//pMap->SetPos(pMap->GetPos() - Vec2(TILE_SIZE * 4 * 5, TILE_SIZE * 4 * 5));
	//
	//pMap->GetTileMap()->Load(pMapPath);
	//pMap->GetTileMap()->SetScale(Vec2(4.f, 4.f));
	//pMap->SetActive(false);
	
	

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
