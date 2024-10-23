#include "pch.h"
#include "Monster.h"

#include "CEngine.h"
#include "CSelectGDI.h"
#include "CTimeMgr.h"
#include "GCamera.h"
#include "GAssetManager.h"
#include "GTexture.h"

#include "Collider.h"
#include "GRigidBody.h"
#include "GFSM.h"

#include "GMIdleState.h"
#include "GMChaseState.h"

Monster::Monster() :
	m_Target(nullptr),
	m_MInfo(),
	m_Dir(),
	m_Texture(nullptr),
	m_HitBox(nullptr),
	m_RigidBody(nullptr),
	m_FSM(nullptr)
{
	m_Texture = (GTexture*)GAssetManager::GetInst()->LoadTexture(L"Monster", L"Texture\\TX_GlowScene_2.png");;

	m_HitBox = AddComponent<Collider>();
	m_HitBox->SetName(L"Monster_Hit_Box");
	m_HitBox->SetPos(Vec2(0, 0));
	m_HitBox->SetScale(Vec2(50.f, 50.f));
	m_HitBox->GetID();

	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetName(L"Monset_RigidBody");
	//m_RigidBody->SetElasticity(1.f);
	m_RigidBody->SetMass(10.f);
	m_RigidBody->SetFriction(0.f);

	m_FSM = AddComponent<GFSM>();
	m_FSM->AddState(L"IDLE", new GMIdleState);
	m_FSM->AddState(L"CHASE", new GMChaseState);
	m_FSM->ChanageState(L"IDLE");
}

Monster::~Monster()
{
}


void Monster::Begin()
{
}

void Monster::Tick()
{

}

void Monster::Render()
{
	Vec2 Pos = GetRenderPos();
	Vec2 Scale = GetScale();

	HDC dc = CEngine::GetInst()->GetSecondDC();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(dc
		, Pos.x - m_Texture->GetWidth() / 2.f
		, Pos.y - m_Texture->GetHeight() / 2.f
		, m_Texture->GetWidth()
		, m_Texture->GetHeight()
		, m_Texture->GetDC()
		, 0, 0
		, m_Texture->GetWidth()
		, m_Texture->GetHeight()
		, blend);
	/*
	{
		SELECT_BRUSH(BRUSH_TYPE::RED);

		Ellipse(CEngine::GetInst()->GetSecondDC(),
			Pos.x - Scale.x / 2.f,
			Pos.y - Scale.y / 2.f,
			Pos.x + Scale.x / 2.f,
			Pos.y + Scale.y / 2.f);
	}
	*/
}

void Monster::EnterOverlap(Collider* _Collider)
{

}



