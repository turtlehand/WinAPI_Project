#include "pch.h"
#include "GLevel_Stage_1.h"

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

GLevel_Stage_1::GLevel_Stage_1() :
	m_Player(nullptr),
	m_Map(nullptr)
{
	SetName(L"Stage_1");
}

GLevel_Stage_1::~GLevel_Stage_1()
{
}

void GLevel_Stage_1::Begin()
{
	DeBugRenderManager::GetInst()->ShowDeBugRender(false);

	// Player 생성하기
	GPlayer* player = new GPlayer;
	player->Awake();
	m_Player = player;
	AddObject(player, LAYER_TYPE::PLAYER);
	if (CLevelMgr::GetInst()->GetPrevLevelType() == LEVEL_TYPE::STAGE0)
	{
		player->SetPos(32.f + 64 * 4, 32.f + 64 * 2);
	}
	else if (CLevelMgr::GetInst()->GetPrevLevelType() == LEVEL_TYPE::STAGE2)
	{
		player->SetPos(32.f + 64 * 12, 32.f + 64 * 21);
	}
	

	GCamera::GetInst()->SetTarget(player);

	GMap* pMap = new GMap;
	m_Map = pMap;
	pMap->Awake();
	AddObject(pMap, LAYER_TYPE::BACKGROUND);
	wstring pMapPath = GPathManager::GetContentPath();
	pMapPath += L"TileMap\\Stage_1.tm";
	pMap->SetName(L"Map");
	pMap->GetTileMap()->SetScale(Vec2(4.f, 4.f));
	pMap->GetTileMap()->Load(pMapPath);
	pMap->GetTileMap()->CreateCreature();


	
	for (int i = 0; i < GetGameObject(LAYER_TYPE::DEFAULT).size(); ++i)
	{
		GLevelChange* NextLevel = dynamic_cast<GLevelChange*>(GetGameObject(LAYER_TYPE::DEFAULT)[i]);
		NextLevel->SetChanageLevel(LEVEL_TYPE::STAGE2);
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

void GLevel_Stage_1::End()
{
	CLevel::End();
	//GCamera::GetInst()->SetTarget(nullptr);
	//GSoundManager::GetInst()->RegisterToBGM(nullptr);
}

void GLevel_Stage_1::Tick()
{
	CLevel::Tick();
}

void GLevel_Stage_1::Render()
{
	CLevel::Render();
}
