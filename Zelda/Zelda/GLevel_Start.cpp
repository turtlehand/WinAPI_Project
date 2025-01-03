#include "pch.h"
#include "GLevel_Start.h"

#include "DeBugRenderManager.h"
#include "GSoundManager.h"
#include "CollisionManager.h"
#include "GCamera.h"

#include "GPlayer.h"

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
	DeBugRenderManager::GetInst()->ShowDeBugRender(false);

	//배경음 지정
	GSound* pSound = GAssetManager::GetInst()->LoadSound(L"Dark_World", L"Sound\\BGM\\Dark_World.wav");
	if (pSound != nullptr)
	{
		pSound->SetVolume(50.f);
		pSound->PlayToBGM(true);
	}

	// Player 생성하기
	GPlayer* player = new GPlayer;
	player->Awake();
	m_Player = player;
	AddObject(player, LAYER_TYPE::PLAYER);

	player->SetPos(32.f + 64 * 4, 32.f + 64 * 4);

	GMap* pMap = new GMap;
	m_Map = pMap;
	pMap->Awake();
	AddObject(pMap, LAYER_TYPE::BACKGROUND);
	wstring pMapPath = GPathManager::GetContentPath();
	pMapPath += L"TileMap\\bug_test.tm";
	pMap->SetName(L"Map");
	pMap->GetTileMap()->SetScale(Vec2(4.f, 4.f));
	pMap->GetTileMap()->Load(pMapPath);
	pMap->GetTileMap()->CreateCreature();

	CollisionManager::GetInst()->CollisionCheckClear();

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::DEFAULT, LAYER_TYPE::PLAYER);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WALL, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WALL, LAYER_TYPE::MONSTER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WALL, LAYER_TYPE::PLAYER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WALL, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WALL, LAYER_TYPE::PLAYER);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WATER, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WATER, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::WATER, LAYER_TYPE::PLAYER);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::OBJECT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::OBJECT, LAYER_TYPE::ITEM);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::OBJECT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::OBJECT, LAYER_TYPE::PLAYER);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_OBJECT, LAYER_TYPE::ITEM);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ITEM);

	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::PLAYER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::PLAYER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::MONSTER);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::MONSTER_OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::OBJECT);
	CollisionManager::GetInst()->CollisionCheck(LAYER_TYPE::ELEMENT, LAYER_TYPE::ITEM);


	GCamera::GetInst()->SetTarget(player);
	GCamera::GetInst()->SetCenter(player->GetGlobalPos());
	GCamera::GetInst()->SetMapSize(Vec2(TILE_SIZE * 4 * m_Map->GetTileMap()->GetCol(), TILE_SIZE * 4 * m_Map->GetTileMap()->GetRow()));
}

void GLevel_Start::End()
{
	CLevel::End();
	GCamera::GetInst()->SetTarget(nullptr);
	GSoundManager::GetInst()->RegisterToBGM(nullptr);
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

	/*
	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos();
	wchar_t buff[255] = {};
	swprintf_s(buff, 255, L"%d, %d", (int)MousePos.x, (int)MousePos.y);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, buff, wcslen(buff));
	*/

	Vec2 MousePos_Window = CKeyMgr::GetInst()->GetMousePos_Window();
	wchar_t buff[255] = {};
	swprintf_s(buff, 255, L"%d, %d", (int)MousePos_Window.x, (int)MousePos_Window.y);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 50, buff, wcslen(buff));
	//TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, m_Player->GetCurrentState().c_str(), m_Player->GetCurrentState().size());
}
