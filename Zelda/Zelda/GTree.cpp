#include "pch.h"
#include "GTree.h"

#include "GBoxCollider.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"
#include "GLog.h"

#include "GAssetManager.h"

GTree::GTree() :
	m_Collider(nullptr),
	m_Sprite(nullptr)
{
	SetName(L"Tree");

	// ³ª¹« ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	m_Collider = AddComponent< GBoxCollider>();
	m_Collider->SetName(L"Tree_HitBox");
	m_Collider->SetScale(Vec2(64.f, 64.f));

	m_Sprite = AddComponent< GSpriteRenderer>();
	m_Sprite->SetSprite(GAssetManager::GetInst()->LoadSprite(L"Tree", L"Sprite\\test_19.sprite"));
	m_Sprite->SetScale(Vec2(4.f, 4.f));
}

GTree::~GTree()
{
}

void GTree::DropItem()
{
	CObj* DropLog = new GLog;
	DropLog->SetPos(GetPos().x,GetPos().y);
	CreateGameObject(DropLog, LAYER_TYPE::OBJECT);
}

void GTree::Begin()
{
}

void GTree::Tick()
{
	GCreature::Tick();
}

void GTree::Render()
{
	m_Sprite->Render();
	RenderEffect();
}

void GTree::EnterOverlap(GCollider* _Collider)
{
	GHitBox* HitBox = dynamic_cast<GHitBox*>(_Collider->GetOwner());
	if (HitBox != nullptr)
		Interaction(HitBox);
}
