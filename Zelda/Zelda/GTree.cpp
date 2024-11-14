#include "pch.h"
#include "GTree.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"
#include "GLog.h"

#include "GAssetManager.h"

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
	CObj* DropLog = new GLog;
	DropLog->SetPos(GetGlobalPos());
	CreateGameObject(DropLog, LAYER_TYPE::OBJECT);
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
