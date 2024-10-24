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

	// Player 생성하기
	Player* player = new Player;
	AddObject(player, LAYER_TYPE::PLAYER);
	player->SetName(L"Player");
	player->SetPos(0.f, 0.f);
	player->SetScale(0, 0);
	

	// Monster 생성하기
	Monster* monster = new Monster;
	AddObject(monster, LAYER_TYPE::MONSTER);
	monster->SetName(L"Monster");
	monster->SetPos(300.f, 200.f);
	monster->SetScale(100, 100);
	monster->GetInfo() = { 100.f,100.f, 0.f, 100.f, 200.f,50.f };
	

	Monster* monster2 = new Monster;
	AddObject(monster2, LAYER_TYPE::MONSTER);
	monster2->SetName(L"Monster2");
	monster2->SetPos(-300.f, 200.f);
	monster2->SetScale(100, 100);
	monster2->GetInfo() = { 100.f,100.f, 0.f, 100.f, 200.f,50.f };
	

	// TileMap Object 추가
	wstring FilePath = GPathManager::GetContentPath();
	GMap* pTileMap = new GMap;
	AddObject(pTileMap, LAYER_TYPE::TILE);
	pTileMap->SetPos(Vec2(0.f, 0.f));
	pTileMap->GetTileMap()->SetAtlasTexture(GAssetManager::GetInst()->LoadTexture(L"Tile", L"Texture\\TILE.bmp"));
	pTileMap->GetTileMap()->Load(FilePath + L"TileMap\\Temp.tile");
	

	// TileMap Object 추가
	pTileMap = new GMap;
	AddObject(pTileMap, LAYER_TYPE::TILE);
	pTileMap->SetPos(Vec2(1000.f, 1000.f));
	pTileMap->GetTileMap()->SetAtlasTexture(GAssetManager::GetInst()->LoadTexture(L"Tile", L"Texture\\TILE.bmp"));
	pTileMap->GetTileMap()->Load(FilePath + L"TileMap\\Temp2.tile");
	

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
