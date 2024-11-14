#include "pch.h"
#include "GLog.h"

#include "GBoxCollider.h"
#include "GRigidBody.h"
#include "GSpriteRenderer.h"

#include "GHitBox.h"

#include "GAssetManager.h"

GLog::GLog() :
	GCreature(CREATURE_ID::Log),
	m_RigidBody(nullptr),
	m_Sprite(nullptr)
{
	SetName(L"Log");

	// ³ª¹« ½ºÅÈ
	DefaultStatsInfo* pInfo = new DefaultStatsInfo;
	pInfo->Material = MATERIAL_TYPE::WOOD;
	pInfo->MaxHP = 4;
	pInfo->HP = 4;
	pInfo->AttackPower = 0;
	pInfo->Speed = 0;
	pInfo->IsDead = false;
	SetStatInfo(pInfo);

	GetHitBox()->SetName(L"Log_HitBox");
	GetHitBox()->SetScale(Vec2(32.f, 64.f));

	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(900.f);

	m_Sprite = AddComponent< GSpriteRenderer>();
	m_Sprite->SetSprite(GAssetManager::GetInst()->LoadSprite(L"Log", L"Sprite\\Object_16\\LOG.sprite"));
	m_Sprite->SetScale(Vec2(4.f, 4.f));

	m_Sprite->SetDeleteColor(RGB(116, 116, 116));
}

GLog::~GLog()
{
}

void GLog::DropItem()
{

}

void GLog::Begin()
{
}

/*
void GLog::Tick()
{
	GCreature::Tick();
}
*/

void GLog::Render()
{
	m_Sprite->Render();
}
