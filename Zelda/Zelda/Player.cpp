#include "pch.h"
#include "Player.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "TaskManager.h"
#include "DeBugRenderManager.h"
#include "GAssetManager.h"
#include "GPathManager.h"
#include "GCamera.h"

#include "CLevel.h"
#include "CSelectGDI.h"

#include "Missile.h"
#include "GuidedMissile.h"

#include "GTexture.h"
#include "GFlipBook.h"
#include "GSprite.h"

#include "GFlipBookPlayer.h"
#include "GRigidBody.h"

enum class PLAYER_ANIM_STATE
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

Player::Player() :
	m_AccTime(0.f),
	m_AttSpeed(0.f),
	m_JumpStack(0.f),
	m_JumpTime(0.f),
	m_MaxJumpTime(0.f),
	m_Collider(nullptr),
	m_FlipBookPlayer(nullptr),
	m_RigidBody(nullptr),
	m_Texture(nullptr)
{
	SetAttSpeed(5);
	SetMaxJumpTime(1.f);
	SetMaxMoveSpeed(200.f);
	SetInitForce(100000.f);

	m_Collider = AddComponent<Collider>();
	m_Collider->SetName(L"Player_Hit_Box");
	m_Collider->SetPos(Vec2(0, 0));
	m_Collider->SetScale(Vec2(64.f, 64.f));
	m_Collider->GetID();

	m_RigidBody = AddComponent<GRigidBody>();
	m_RigidBody->SetName(L"Player_RigidBody");
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetFriction(900.f);
	
	//m_RigidBody->SetElasticity(1.f);
	//m_RigidBody->SetGravity(Vec2(0.f,98.f));

	// 절대경로, 객체 중복 로딩 방지
	//m_Texture = GAssetManager::GetInst()->LoadTexture(L"PlayerTexture", L"Fighter.bmp");

	CreatePlayerFlipBook();

}

Player::~Player()
{
	DELETEGAMEOBJECT(m_Texture);
}


void Player::Begin()
{
	m_FlipBookPlayer->Play(0,2,true);
	//GCamera::GetInst()->SetTarget((CObj*)this);
}

void Player::Tick()
{
	Move();
	//Jump();
	Shot();
}

void Player::Move()
{
	//m_FlipBookPlayer->SetXFlip(false);
	//m_FlipBookPlayer->SetYFlip(false);

	if (GETKEYDOWN(KEY::LEFT))
	{
		m_FlipBookPlayer->SetXFlip(true);
		m_FlipBookPlayer->Play((int)PLAYER_ANIM_STATE::RIGHT, 2.f, true);
	}
	else if (GETKEYDOWN(KEY::RIGHT))
	{
		m_FlipBookPlayer->SetXFlip(false);
		m_FlipBookPlayer->Play((int)PLAYER_ANIM_STATE::RIGHT, 2.f, true);
	}
	else if (GETKEYDOWN(KEY::UP))
	{
		m_FlipBookPlayer->SetYFlip(true);
		m_FlipBookPlayer->SetXFlip(false);
		m_FlipBookPlayer->Play((int)PLAYER_ANIM_STATE::DOWN, 2.f, true);
	}
	else if (GETKEYDOWN(KEY::DOWN))
	{
		m_FlipBookPlayer->SetYFlip(false);
		m_FlipBookPlayer->SetXFlip(false);
		m_FlipBookPlayer->Play((int)PLAYER_ANIM_STATE::DOWN, 2.f, true);
	}
	
	
	if (GETKEYPRESSED(KEY::LEFT))
	{
		m_RigidBody->AddForce(Vec2(-1000.f, 0.f));
		AddInitForce(Vec2(-1.f, 0.f), m_InitForce);
	}
	if (GETKEYPRESSED(KEY::RIGHT))
	{
		m_RigidBody->AddForce(Vec2(1000.f, 0.f));
		AddInitForce(Vec2(1.f, 0.f), m_InitForce);
	}
	if (GETKEYPRESSED(KEY::UP))
	{
		m_RigidBody->AddForce(Vec2(0.f, 1000.f));
		AddInitForce(Vec2(0.f, 1.f), m_InitForce);
	}
	if (GETKEYPRESSED(KEY::DOWN))
	{
		m_RigidBody->AddForce(Vec2(0.f, -1000.f));
		AddInitForce(Vec2(0.f, -1.f), m_InitForce);
	}

	CalMaxMoveSpeed();

	DrawDebugLine(PEN_TYPE::BLUE, 0.f, GetPos(), GetPos() + m_RigidBody->GetVelocity());
}

void Player::CalMaxMoveSpeed()
{
	float Speed = m_RigidBody->GetVelocity().Length();

	if (Speed != 0)
	{
		Speed = m_MaxMoveSpeed >= Speed ? Speed : m_MaxMoveSpeed;
		m_RigidBody->SetVelocity(m_RigidBody->GetVelocity().Normalize() * Speed);
	}
}

/// <summary>
/// 속도가 0일 때 빠른 움직임을 위한 추가속도
/// </summary>
void Player::AddInitForce(Vec2 _Dir, float _Force)
{
	_Dir = _Dir.Normalize();
	float Speed = m_RigidBody->GetVelocity().Length();
	
	if (Speed == 0)
	{
		m_RigidBody->AddForce(_Dir * _Force);
	}
	
}

void Player::Jump()
{
	if (GETKEYPRESSED(KEY::SPACE) && m_JumpStack && (m_JumpTime <= m_MaxJumpTime))
	{
		m_JumpTime += DT;
		m_RigidBody->SetVelocity(Vec2(m_RigidBody->GetVelocity().x, 100.f));
	}

	if (GETKEYUP(KEY::SPACE))
	{
		m_JumpTime = 0;
    	m_JumpStack = m_JumpStack > 0 ? --m_JumpStack : 0;
	}
}

void Player::Shot()
{
	m_AccTime += (float)DT;
	
	// 발사 대기 시간이 초당 발사 속도보다 작다면 무시
	if (1.f / m_AttSpeed > m_AccTime)
		return;

	if (GETKEYPRESSED(KEY::SPACE))
	{
		m_AccTime = 0;

		GuidedMissile* pMissile = new GuidedMissile;

		pMissile->SetName(L"Missile");
		pMissile->SetPos(GetPos().x, GetPos().y + 5);
		pMissile->SetScale(10, 10);
		pMissile->SetVelocity(Vec2(cosf(PI /2.f), sinf(PI / 2.f) * 400.f));
		pMissile->SetDetectRange(400.f);
		

		CreateGameObject(pMissile, LAYER_TYPE::PLAYER_OBJECT);

	}
}


void Player::Render()
{
	m_FlipBookPlayer->Render();

	/*
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();

	UINT Width = m_Texture->GetWidth();
	UINT Height = m_Texture->GetHeight();
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();

	TransparentBlt(hBackDC,
		Pos.x - (Width / 2),
		Pos.y - (Height / 2),
		Width, Height,
		m_Texture->GetDC(),
		0, 0, Width, Height, RGB(255, 0, 255));
	*/
}

void Player::EnterOverlap(Collider* _Collider)
{
	if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::DEFAULT)
		m_JumpStack = 2;
}

void Player::CreatePlayerFlipBook()
{
	// AtlasTexture
	GTexture* pAtlas = GAssetManager::GetInst()->LoadTexture(L"Link", L"Texture\\link_32.bmp");

	
	/*
	CreateFlipBook(L"LINK_IDLE_DOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.), 3);
	CreateFlipBook(L"LINK_IDLE_LEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.), 3);
	CreateFlipBook(L"LINK_IDLE_UP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.), 1);
	CreateFlipBook(L"LINK_IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.), 3);

	CreateFlipBook(L"LINK_MOVE_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.), 10);
	CreateFlipBook(L"LINK_MOVE_LEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.), 10);
	CreateFlipBook(L"LINK_MOVE_UP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.), 10);
	CreateFlipBook(L"LINK_MOVE_RIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.), 10);
	*/

	// FlipbookPlayer 컴포넌트 추가하기
	m_FlipBookPlayer = AddComponent<GFlipBookPlayer>();
	m_FlipBookPlayer->AddFlipBook((int)PLAYER_ANIM_STATE::DOWN, GAssetManager::GetInst()->LoadFlipBook(L"LINK_DOWN", L"FlipBook\\Link_16\\LINK_DOWN.flip"));
	//m_FlipBookPlayer->AddFlipBook((int)PLAYER_ANIM_STATE::LEFT, GAssetManager::GetInst()->LoadFlipBook(L"LINK_LEFT", L"FlipBook\\LINK_IDLE_LEFT.flip"));
	m_FlipBookPlayer->AddFlipBook((int)PLAYER_ANIM_STATE::UP, GAssetManager::GetInst()->LoadFlipBook(L"LINK_UP", L"FlipBook\\Link_16\\LINK_UP.flip"));
	m_FlipBookPlayer->AddFlipBook((int)PLAYER_ANIM_STATE::RIGHT, GAssetManager::GetInst()->LoadFlipBook(L"LINK_RIGHT", L"FlipBook\\Link_16\\LINK_RIGHT.flip"));

	m_FlipBookPlayer->SetScale(Vec2(4.f, 4.f));

	//m_FlipBookPlayer->SetAlpha(127);
	m_FlipBookPlayer->SetDeleteColor(RGB(116, 116, 116));

}

void Player::CreateFlipBook(const wstring& _FlipBookName, GTexture* _Atlas, Vec2 _LftTop, Vec2 _Slice, int MaxFrame)
{
	
	
	// Link_MOVEDOWN Sprite 생성기
	/*
	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipBookName + L"_%d").c_str(), i);

		GSprite* pSprite = new GSprite;
		pSprite->Create(_Atlas, _LftTop + Vec2(120.f, 0.f) * i , _Slice);
		GAssetManager::GetInst()->AddSprite(Key, pSprite);

		wstring strSavePath = L"Sprite\\";
		strSavePath += pSprite->GetKey();
		pSprite->Save(strSavePath);
	}
	*/
	
	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipBookName + L"_%d").c_str(), i);
		wstring Path = L"Sprite\\";
		Path += Key;
		Path += L".sprite";
		GAssetManager::GetInst()->LoadSprite(Key, Path);
	}
	
	
	/*
	// FlipBook 생성하기
	GFlipBook* pFlipBook = new GFlipBook;

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipBookName + L"_%d").c_str(), i);
		pFlipBook->AddSprite(GAssetManager::GetInst()->FindSprite(Key));
	}

	GAssetManager::GetInst()->AddFlipBook(_FlipBookName, pFlipBook);

	wstring strSavePath = L"FlipBook\\";
	strSavePath += pFlipBook->GetKey();
	pFlipBook->Save(strSavePath);
	*/
}


