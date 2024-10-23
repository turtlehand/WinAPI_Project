#include "pch.h"
#include "GFlipBookPlayer.h"

#include "CTimeMgr.h"
#include "GFlipBook.h"
#include "GCamera.h"

#include "CEngine.h"
#include "GSprite.h"
#include "GTexture.h"

GFlipBookPlayer::GFlipBookPlayer() :
	Component(COMPONENT_TYPE::FILPBOOKPLAYER),
	m_vecFlipBook(),
	m_CurFlipBook(nullptr),
	m_SpriteIdx(0),
	m_FPS(0.f),
	m_Time(0.f),
	m_Repeat(true),
	m_Finish(false)
{
}

GFlipBookPlayer::~GFlipBookPlayer()
{
}

void GFlipBookPlayer::FinalTick()
{
	//���� ������� FlipBook�� ������ ��
	if (nullptr == m_CurFlipBook)
	{
		return;
	}

	if (m_Finish)
	{
		// 1. �ݺ���� -> 0�� �ε����� ����
		// �ݺ� ����ϱ�� ������ 0�� ��������Ʈ�� �ε����� �����Ѵ�.
		if (m_Repeat)
			Reset();
		// 2. �ѹ���� -> ������ ��������Ʈ �ε����� ����
		// �ѹ� ����� ������(m_Finish), �ݺ� �����尡 �ƴ϶��
		// ������ �������� �����ϵ��� �Ѵ�.
		else return;
	}

	// FPS �� ���� �ð�üũ

	m_Time += DT;
	if (1.f / m_FPS <= m_Time)
	{
		m_Time -= 1.f / m_FPS;
		++m_SpriteIdx;

		// ������ Sprite�� �����ߴٸ�
		if (m_CurFlipBook->GetMaxSpriteCount() <= m_SpriteIdx)
		{
			m_Finish = true;
			--m_SpriteIdx;
		}
	}
}

void GFlipBookPlayer::Render()
{
	if (nullptr == m_CurFlipBook)
		return;

	GSprite* Sprite = m_CurFlipBook->GetSprite(m_SpriteIdx);

	// Sprite �� ȭ�鿡 �׸���.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	TransparentBlt(hBackDC
		, vPos.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x
		, vPos.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y
		, Sprite->GetSlice().x
		, Sprite->GetSlice().y
		, Sprite->GetAtlas()->GetDC()
		, Sprite->GetLeftTop().x
		, Sprite->GetLeftTop().y
		, Sprite->GetSlice().x
		, Sprite->GetSlice().y
		, RGB(255, 0, 255));
}
