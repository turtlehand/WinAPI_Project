#include "pch.h"
#include "GLevel_Stage_2.h"

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

GLevel_Stage_2::GLevel_Stage_2() :
	m_Player(nullptr),
	m_Map(nullptr)
{
	SetName(L"Stage_2");
}

GLevel_Stage_2::~GLevel_Stage_2()
{
}

void GLevel_Stage_2::Begin()
{
	DeBugRenderManager::GetInst()->ShowDeBugRender(false);

	// Player �����ϱ�
	GPlayer* player = new GPlayer;
	player->Awake();
	m_Player = player;
	AddObject(player, LAYER_TYPE::PLAYER);

	if (CLevelMgr::GetInst()->GetPrevLevelType() == LEVEL_TYPE::STAGE1)
	{
		player->SetPos(32.f + 64 * 6, 32.f + 64 * 3);
	}
	else if (CLevelMgr::GetInst()->GetPrevLevelType() == LEVEL_TYPE::STAGE3)
	{
		player->SetPos(32.f + 64 * 2, 32.f + 64 * 21);
	}

	GCamera::GetInst()->SetTarget(player);

	GMap* pMap = new GMap;
	m_Map = pMap;
	pMap->Awake();
	AddObject(pMap, LAYER_TYPE::BACKGROUND);
	wstring pMapPath = GPathManager::GetContentPath();
	pMapPath += L"TileMap\\Stage_2.tm";
	pMap->SetName(L"Map");
	pMap->GetTileMap()->SetScale(Vec2(4.f, 4.f));
	pMap->GetTileMap()->Load(pMapPath);
	pMap->GetTileMap()->CreateCreature();


	
	for (int i = 0; i < 3; ++i)
	{
		GLevelChange* NextLevel = dynamic_cast<GLevelChange*>(GetGameObject(LAYER_TYPE::DEFAULT)[i]);
		NextLevel->SetChanageLevel(LEVEL_TYPE::STAGE1);
	}

	for (int i = 3; i < 6; ++i)
	{
		GLevelChange* NextLevel = dynamic_cast<GLevelChange*>(GetGameObject(LAYER_TYPE::DEFAULT)[i]);
		NextLevel->SetChanageLevel(LEVEL_TYPE::STAGE3);
	}
	

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
}

void GLevel_Stage_2::End()
{
	CLevel::End();
	//GCamera::GetInst()->SetTarget(nullptr);
	//GSoundManager::GetInst()->RegisterToBGM(nullptr);
}

void GLevel_Stage_2::Tick()
{
	CLevel::Tick();
}

void GLevel_Stage_2::Render()
{
	CLevel::Render();
}