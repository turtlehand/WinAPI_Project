#include "pch.h"
#include "GTree.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"
#include "GLog.h"

#include "GAssetManager.h"
#include "GPrefabManager.h"

GTree::GTree() :
	GCreature(CREATURE_ID::Tree),
	m_Sprite(nullptr)
{
	SetName(L"Tree");
	SetTitleSprite(GAssetManager::GetInst()->LoadSprite(L"Tree", L"Sprite\\Object_16\\TREE.sprite"));
}

GTree::~GTree()
{
}

void GTree::DropItem()
{
	CObj* Element = GetElement();
	if (IsValid(Element))
		return;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 2);

	int RandomIndex = dist(gen);

	if (RandomIndex == 0 || RandomIndex == 1)
	{
		CObj* Log = GPrefabManager::GetInst()->CreatePrefab(CREATURE_ID::Log);
		if (GetParent() != nullptr)
		{

			CreateChildGameObject(GetParent(), Log, LAYER_TYPE::OBJECT);
			Log->SetPos(GetPos());
		}
		else
		{
			CreateGameObject(Log, LAYER_TYPE::OBJECT);
			Log->SetPos(GetPos());
		}
	}
	else if (RandomIndex == 2)
	{
		CObj* Fruit = GPrefabManager::GetInst()->CreatePrefab(CREATURE_ID::Fruit);
		if (GetParent() != nullptr)
		{

			CreateChildGameObject(GetParent(), Fruit, LAYER_TYPE::ITEM);
			Fruit->SetPos(GetPos());
		}
		else
		{
			CreateGameObject(Fruit, LAYER_TYPE::ITEM);
			Fruit->SetPos(GetPos());
		}
	}

}

void GTree::Awake()
{
	GCreature::Awake();

	// ³ª¹« ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	GetHitBox()->SetName(L"Tree_HitBox");
	GetHitBox()->SetScale(Vec2(64.f, 64.f));

	m_Sprite = AddComponent< GSpriteRenderer>();
	m_Sprite->SetSprite(GAssetManager::GetInst()->LoadSprite(L"Tree", L"Sprite\\Object_16\\TREE.sprite"));
	m_Sprite->SetScale(Vec2(4.f, 4.f));
	m_Sprite->SetDeleteColor(RGB(252, 216, 168));
}
/*
void GTree::Tick()
{
	GCreature::Tick();
}
*/
void GTree::Render()
{
	m_Sprite->Render();
}
