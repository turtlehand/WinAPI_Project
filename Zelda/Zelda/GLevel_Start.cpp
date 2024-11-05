#include "pch.h"
#include "GLevel_Start.h"

#include "CollisionManager.h"

#include "Player.h"
#include "Monster.h"
#include "GPlatform.h"
#include "GHitBox.h"
#include "GRock.h"

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

	GHitBox* pAttackBox = new GHitBox;
	AddObject(pAttackBox, LAYER_TYPE::PLAYER_OBJECT);
	pAttackBox->SetName(L"Player_AttackBox");
	pAttackBox->SetPos(0.f, 0.f);
	pAttackBox->SetScale(0, 0);

	// Player 스탯
	PlayerInfo* pInfo = new PlayerInfo;
	pInfo->Material = MATERIAL_TYPE::LIFE;
	pInfo->MaxHP = 12;
	pInfo->HP = 12;
	pInfo->AttackPower = 0;
	pInfo->Speed = 128;
	pInfo->Direction = Vec2::down();
	pInfo->IsDead = false;

	// Player 생성하기
	Player* player = new Player;
	player->AddChild(pAttackBox);
	player->SetStatInfo(pInfo);
	m_Player = player;
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
	//monster->GetInfo() = { 100.f,100.f, 0.f, 100.f, 200.f,50.f };
	

	GRock* pRock = new GRock;
	AddObject(pRock, LAYER_TYPE::OBJECT);
	pRock->SetName(L"Rock");
	pRock->SetPos(-300.f, 200.f);
	//monster2->GetInfo() = { 100.f,100.f, 0.f, 100.f, 200.f,50.f };
	

	// TileMap Object 추가
	wstring FilePath = GPathManager::GetContentPath();
	GMap* pTileMap = new GMap;
	AddObject(pTileMap, LAYER_TYPE::TILE);
	pTileMap->SetPos(Vec2(0.f, 0.f));
	//pTileMap->GetTileMap()->SetAtlasTexture(GAssetManager::GetInst()->LoadTexture(L"Tile", L"Texture\\TILE.bmp"));
	//pTileMap->GetTileMap()->Load(FilePath + L"TileMap\\Temp.tile");
	

	// TileMap Object 추가
	pTileMap = new GMap;
	AddObject(pTileMap, LAYER_TYPE::TILE);
	pTileMap->SetPos(Vec2(1000.f, 1000.f));
	//pTileMap->GetTileMap()->SetAtlasTexture(GAssetManager::GetInst()->LoadTexture(L"Tile", L"Texture\\TILE.bmp"));
	//pTileMap->GetTileMap()->Load(FilePath + L"TileMap\\Temp2.tile");
	

	CollisionManager::GetInst()->CollisionCheckClear();
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

	CLevel::Begin();
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
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, m_Player->GetCurrentState().c_str(), m_Player->GetCurrentState().size());
}
