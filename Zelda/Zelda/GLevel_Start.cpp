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
	GSound* pSound = GAssetManager::GetInst()->LoadSound(L"Start_Level", L"Sound\\BGM_Stage1.wav");

	if (pSound != nullptr)
	{
		pSound->SetVolume(1.f);
		pSound->PlayToBGM(true);

	}

	// Player 스탯


	// Player 생성하기
	GPlayer* player = new GPlayer;
	m_Player = player;
	AddObject(player, LAYER_TYPE::PLAYER);
	player->SetPos(0.f, 0.f);


	// Monster 생성하기
	GMoblin* pMoblin = new GMoblin;
	AddObject(pMoblin, LAYER_TYPE::MONSTER);
	pMoblin->SetPos(300.f, 200.f);
	

	GRock* pRock = new GRock;
	AddObject(pRock, LAYER_TYPE::OBJECT);
	pRock->SetPos(-300.f, 200.f);

	GTree* pTree = new GTree;
	AddObject(pTree, LAYER_TYPE::OBJECT);
	pTree->SetPos(-300.f, 100.f);
	

	// TileMap Object 추가
	GMap* pTileMap = new GMap;
	AddObject(pTileMap, LAYER_TYPE::TILE);
	pTileMap->SetPos(Vec2(0.f, 0.f));

	GRock* pRock2 = new GRock;
	AddObject(pRock2, LAYER_TYPE::OBJECT);
	pRock2->SetPos(0, 0);
	

	// TileMap Object 추가
	pTileMap = new GMap;
	AddObject(pTileMap, LAYER_TYPE::TILE);
	pTileMap->SetPos(Vec2(1000.f, 1000.f));
	

	CollisionManager::GetInst()->CollisionCheckClear();
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
}

void GLevel_Start::Tick()
{
	CLevel::Tick();
	

	if (GETKEYDOWN(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}

void GLevel_Start::Render()
{
	CLevel::Render();

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Start Level", wcslen(L"Start Level"));
	//TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, m_Player->GetCurrentState().c_str(), m_Player->GetCurrentState().size());
}
