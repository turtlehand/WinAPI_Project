#include "pch.h"
#include "GLevel_Start.h"

#include "CollisionManager.h"

#include "Player.h"
#include "Monster.h"
#include "GPlatform.h"
#include "GPathManager.h"

#include "GMap.h"
#include "GTileMap.h"
#include "GAssetManager.h"
#include "GSound.h"

GLevel_Start::GLevel_Start()
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

	// Player �����ϱ�
	Player* player = new Player;
	player->SetName(L"Player");
	player->SetPos(0.f, 0.f);
	player->SetScale(0, 0);
	AddObject(player, LAYER_TYPE::PLAYER);

	// Monster �����ϱ�
	Monster* monster = new Monster;
	monster->SetName(L"Monster");
	monster->SetPos(300.f, 200.f);
	monster->SetScale(100, 100);
	monster->GetInfo() = { 100.f,100.f, 0.f, 100.f, 200.f,50.f };
	AddObject(monster, LAYER_TYPE::MONSTER);

	Monster* monster2 = new Monster;
	monster2->SetName(L"Monster2");
	monster2->SetPos(-300.f, 200.f);
	monster2->SetScale(100, 100);
	monster2->GetInfo() = { 100.f,100.f, 0.f, 100.f, 200.f,50.f };
	AddObject(monster2, LAYER_TYPE::MONSTER);

	// TileMap Object �߰�
	GMap* pTileMap = new GMap;
	pTileMap->SetPos(Vec2(0.f, 0.f));
	wstring FilePath = GPathManager::GetContentPath();
	pTileMap->GetTileMap()->Load(FilePath + L"TileMap\\Temp.tile");
	AddObject(pTileMap, LAYER_TYPE::TILE);

	// TileMap Object �߰�
	pTileMap = new GMap;
	pTileMap->SetPos(Vec2(1000.f, 1000.f));
	pTileMap->GetTileMap()->Load(FilePath + L"TileMap\\Temp2.tile");
	AddObject(pTileMap, LAYER_TYPE::TILE);

	CollisionManager::GetInst()->CollisionCheckClear();
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

	CLevel::Begin();
}

void GLevel_Start::Tick()
{
	CLevel::Tick();
	

	if (GETKEYDOWN(KEY::NUM8))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}

void GLevel_Start::Render()
{
	CLevel::Render();

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Start Level", wcslen(L"Start Level"));
}
