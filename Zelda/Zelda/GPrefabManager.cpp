#include "pch.h"
#include "GPrefabManager.h"
#include "GCreature.h"

#include "GMoblin.h"

// 오브젝트
#include "GGrass.h"
#include "GTree.h"
#include "GLog.h"
#include "GRock.h"
#include "GPullRock.h"

// 아이템
#include "GFireWood.h"
#include "GFlint.h"
#include "GFruit.h"
#include "GRoastFruit.h"
#include "GWeapon.h"
#include "GBow.h"

// 공격
#include "GFire.h"

// 벽
#include "GWall.h"
#include "GLevelChange.h"

GPrefabManager::GPrefabManager()
{

}

GPrefabManager::~GPrefabManager()
{
	Delete_Map(m_mapPrefab);
}

void GPrefabManager::Init()
{
	// 몬스터
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Moblin, new GMoblin));

	// 오브젝트
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Grass, new GGrass));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Tree, new GTree));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Log, new GLog));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Rock, new GRock));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::PullRock, new GPullRock));

	// 아이템
	// 소재
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Fire_Wood, new GFireWood));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Flint, new GFlint));
	
	// 음식
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Fruit, new GFruit));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Roast_Fruit, new GRoastFruit));

	// 무기
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Wooden_Sword, new GWeapon(CREATURE_ID::Wooden_Sword)));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Iron_Sword, new GWeapon(CREATURE_ID::Iron_Sword)));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Stone_Hammer, new GWeapon(CREATURE_ID::Stone_Hammer)));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Branch, new GWeapon(CREATURE_ID::Branch)));

	// 도구
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Bow, new GBow));

	// 공격 박스
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::HitBox, new GHitBox));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Fire, new GFire));

	// 기타
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Wall, new GWall(CREATURE_ID::Wall)));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::Water, new GWall(CREATURE_ID::Water)));
	m_mapPrefab.insert(make_pair((UINT)CREATURE_ID::LevelChange, new GLevelChange));


}


const CObj* GPrefabManager::FindPrefab(CREATURE_ID _Key)
{
	map<UINT, CObj*>::iterator iter = m_mapPrefab.find((int)_Key);

	if (iter == m_mapPrefab.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

CObj* GPrefabManager::CreatePrefab(CREATURE_ID _Key)
{
	CObj* CreatureObj = nullptr;

	switch (_Key)
	{
		// 몬스터
	case CREATURE_ID::Moblin:
	{
		CreatureObj = new GMoblin;
	}
	break;
	// 오브젝트
	case CREATURE_ID::Grass:
	{
		CreatureObj = new GGrass;
	}
	break;

	case CREATURE_ID::Tree:
	{
		CreatureObj = new GTree;
	}
	break;

	case CREATURE_ID::Log:
	{
		CreatureObj = new GLog;
	}
	break;

	case CREATURE_ID::Rock:
	{
		CreatureObj = new GRock;
	}
	break;

	case CREATURE_ID::PullRock:
	{
		CreatureObj = new GPullRock;
	}
	break;

	// 아이템
	case CREATURE_ID::Fire_Wood:
	{
		CreatureObj = new GFireWood;
	}
	break;

	case CREATURE_ID::Flint:
	{
		CreatureObj = new GFlint;
	}
	break;

	case CREATURE_ID::Fruit:
	{
		CreatureObj = new GFruit;
	}
	break;

	case CREATURE_ID::Roast_Fruit:
	{
		CreatureObj = new GRoastFruit;
	}
	break;

	case CREATURE_ID::Wooden_Sword:
	{
		CreatureObj = new GWeapon(CREATURE_ID::Wooden_Sword);
	}
	break;

	case CREATURE_ID::Iron_Sword:
	{
		CreatureObj = new GWeapon(CREATURE_ID::Iron_Sword);
	}
	break;

	case CREATURE_ID::Stone_Hammer:
	{
		CreatureObj = new GWeapon(CREATURE_ID::Stone_Hammer);
	}
	break;

	case CREATURE_ID::Branch:
	{
		CreatureObj = new GWeapon(CREATURE_ID::Branch);
	}
	break;

	case CREATURE_ID::Bow:
	{
		CreatureObj = new GBow;
	}
	break;

	// 공격
	case CREATURE_ID::HitBox:
	{
		CreatureObj = new GHitBox;
	}
	break;

	case CREATURE_ID::Fire:
	{
		CreatureObj = new GFire;
	}
	break;

	// 벽
	case CREATURE_ID::Wall:
	{
		CreatureObj = new GWall(CREATURE_ID::Wall);
	}
	break;

	// 물
	case CREATURE_ID::Water:
	{
		CreatureObj = new GWall(CREATURE_ID::Water);
	}
	break;

	// 물
	case CREATURE_ID::LevelChange:
	{
		CreatureObj = new GLevelChange;
	}
	break;

	}

	return CreatureObj;
}
