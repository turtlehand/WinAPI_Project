#include "pch.h"
#include "GLevel_Stage_0.h"

#include "CLevelMgr.h"

#include "DeBugRenderManager.h"
#include "GSoundManager.h"
#include "CollisionManager.h"
#include "GCamera.h"

#include "GPlayer.h"
#include "GLevelChange.h"

#include "GPathManager.h"

#include "GMap.h"
#include "GTileMap.h"
#include "GAssetManager.h"
#include "GSound.h"

GLevel_Stage_0::GLevel_Stage_0() :
	m_Player(nullptr),
	m_Map(nullptr)
{
	SetName(L"Stage_0");
}

GLevel_Stage_0::~GLevel_Stage_0()
{
}

void GLevel_Stage_0::Begin()
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
	pMapPath += L"TileMap\\Stage_0.tm";
	pMap->SetName(L"Map");
	pMap->GetTileMap()->SetScale(Vec2(4.f, 4.f));
	pMap->GetTileMap()->Load(pMapPath);
	pMap->GetTileMap()->CreateCreature();

	GLevelChange* NextLevel = dynamic_cast<GLevelChange*>(GetGameObject(LAYER_TYPE::DEFAULT)[0]);
	NextLevel->SetChanageLevel(LEVEL_TYPE::STAGE1);


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

void GLevel_Stage_0::End()
{
	CLevel::End();
	//GCamera::GetInst()->SetTarget(nullptr);
	//GSoundManager::GetInst()->RegisterToBGM(nullptr);
}

void GLevel_Stage_0::Tick()
{
	CLevel::Tick();

	if (GETKEYDOWN(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}

void GLevel_Stage_0::Render()
{
	CLevel::Render();
}
