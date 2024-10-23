#include "pch.h"
#include "GFlipBookPlayer.h"

#include "GAssetManager.h"

#include "CTimeMgr.h"
#include "GFlipBook.h"
#include "GCamera.h"

#include "CEngine.h"
#include "GSprite.h"
#include "GTexture.h"

GFlipBookPlayer::GFlipBookPlayer() :
	GComponent(COMPONENT_TYPE::FILPBOOKPLAYER),
	m_vecFlipBook(),
	m_CurFlipBook(nullptr),
	m_SpriteIdx(0),
	m_Scale(1.f,1.f),
	m_DeleteColor(RGB(-1,-1,-1)),
	m_XFlip(false),
	m_YFlip(false),
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
	//현재 재생준인 FlipBook이 없으면 끝
	if (nullptr == m_CurFlipBook)
	{
		return;
	}

	if (m_Finish)
	{
		// 1. 반복재생 -> 0번 인덱스로 변경
		// 반복 재생하기로 했으면 0번 스프라이트로 인덱스를 변경한다.
		if (m_Repeat)
			Reset();
		// 2. 한번재생 -> 마지막 스프라이트 인덱스를 유지
		// 한번 재생이 끝났고(m_Finish), 반복 재생모드가 아니라면
		// 마지막 프레임을 유지하도록 한다.
		else return;
	}

	// FPS 에 따른 시간체크

	m_Time += DT;
	if (1.f / m_FPS <= m_Time)
	{
		m_Time -= 1.f / m_FPS;
		++m_SpriteIdx;

		// 마지막 Sprite에 도달했다면
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

	// Sprite 를 화면에 그린다.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	// 각종 연산을 위한 임시 텍스쳐
	GTexture* TempTexture = GAssetManager::GetInst()->CreateTexture(L"Temp", Sprite->GetSlice().x, Sprite->GetSlice().y);

	StretchBlt(TempTexture->GetDC(),
		0,
		0,
		Sprite->GetSlice().x,
		Sprite->GetSlice().y,
		Sprite->GetAtlas()->GetDC(),
		Sprite->GetLeftTop().x,
		Sprite->GetLeftTop().y,
		Sprite->GetSlice().x,
		Sprite->GetSlice().y,
		SRCCOPY);

	// 반전
	if (m_XFlip)
	{

		StretchBlt(TempTexture->GetDC(),
			Sprite->GetSlice().x - 1,
			0,
			-(Sprite->GetSlice().x + 1),
			Sprite->GetSlice().y,
			Sprite->GetAtlas()->GetDC(),
			Sprite->GetLeftTop().x,
			Sprite->GetLeftTop().y,
			Sprite->GetSlice().x,
			Sprite->GetSlice().y,
			SRCCOPY);
		
	}
	if (m_YFlip)
	{

		StretchBlt(TempTexture->GetDC(),
			0,
			Sprite->GetSlice().y - 1,
			Sprite->GetSlice().x,
			-(Sprite->GetSlice().y + 1),
			Sprite->GetAtlas()->GetDC(),
			Sprite->GetLeftTop().x,
			Sprite->GetLeftTop().y,
			Sprite->GetSlice().x,
			Sprite->GetSlice().y,
			SRCCOPY);
	}
	
	TransparentBlt(hBackDC
		, vPos.x - (Sprite->GetSlice().x / 2) * m_Scale.x + Sprite->GetOffset().x
		, vPos.y - (Sprite->GetSlice().y / 2) * m_Scale.y + Sprite->GetOffset().y
		, Sprite->GetSlice().x * m_Scale.x
		, Sprite->GetSlice().y * m_Scale.y
		, TempTexture->GetDC()
		, 0
		, 0
		, Sprite->GetSlice().x
		, Sprite->GetSlice().y
		, RGB(116, 116, 116));
	
	GAssetManager::GetInst()->DeleteTexture(L"Temp");
}
