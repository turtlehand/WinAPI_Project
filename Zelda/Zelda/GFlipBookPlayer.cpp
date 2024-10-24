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
	m_Alpha(255),
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

void GFlipBookPlayer::XFlip(GTexture*& _Textrue)
{
	GTexture* TempTexture = GAssetManager::GetInst()->CreateTexture(L"XFlip", _Textrue->GetWidth(), _Textrue->GetHeight());

	StretchBlt(TempTexture->GetDC(),
		_Textrue->GetWidth() - 1,
		0,
		-((int)_Textrue->GetWidth()),
		_Textrue->GetHeight(),
		_Textrue->GetDC(),
		0,
		0,
		_Textrue->GetWidth(),
		_Textrue->GetHeight(),
		SRCCOPY);

	GAssetManager::GetInst()->DeleteTexture(_Textrue->GetKey());

	_Textrue = TempTexture;
}

void GFlipBookPlayer::YFlip(GTexture*& _Textrue)
{
	GTexture* TempTexture = GAssetManager::GetInst()->CreateTexture(L"YFlip", _Textrue->GetWidth(), _Textrue->GetHeight());

	StretchBlt(TempTexture->GetDC(),
		0,
		_Textrue->GetHeight() - 1,
		_Textrue->GetWidth(),
		-((int)_Textrue->GetHeight()),
		_Textrue->GetDC(),
		0,
		0,
		_Textrue->GetWidth(),
		_Textrue->GetHeight(),
		SRCCOPY);

	GAssetManager::GetInst()->DeleteTexture(_Textrue->GetKey());

	_Textrue = TempTexture;
}

void GFlipBookPlayer::DeleteColorAlpha(GTexture*& _Textrue)
{
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	GSprite* Sprite = m_CurFlipBook->GetSprite(m_SpriteIdx);

	GTexture* TempTexture = GAssetManager::GetInst()->CreateTexture(L"DeleteColorAlpha", _Textrue->GetWidth() * m_Scale.x, _Textrue->GetHeight() * m_Scale.y);

	// 임시 텍스쳐에 배경 복사
	BitBlt(TempTexture->GetDC()
		, 0
		, 0
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, hBackDC
		, vPos.x - TempTexture->GetWidth() / 2 + Sprite->GetOffset().x
		, vPos.y - TempTexture->GetHeight() / 2 + Sprite->GetOffset().y
		, SRCCOPY);

	// 스프라이트 배경 없애고 텍스쳐에 그리기
	TransparentBlt(TempTexture->GetDC()
		, 0
		, 0
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, _Textrue->GetDC()
		, 0
		, 0
		, _Textrue->GetWidth()
		, _Textrue->GetHeight()
		, m_DeleteColor);

	// 텍스쳐를 배경에 반투명하게 그리기
	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = m_Alpha;
	blend.AlphaFormat = 0;

	AlphaBlend(hBackDC
		, vPos.x - TempTexture->GetWidth() / 2 + Sprite->GetOffset().x
		, vPos.y - TempTexture->GetHeight() / 2 + Sprite->GetOffset().y
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, TempTexture->GetDC()
		, 0, 0
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, blend);

	GAssetManager::GetInst()->DeleteTexture(TempTexture->GetKey());
}


void GFlipBookPlayer::DeleteColor(GTexture*& _Textrue)
{
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	GSprite* Sprite = m_CurFlipBook->GetSprite(m_SpriteIdx);

	// 스프라이트 배경 없애고 텍스쳐에 그리기
	TransparentBlt(hBackDC
		, vPos.x - _Textrue->GetWidth() * m_Scale.x / 2 + Sprite->GetOffset().x
		, vPos.y - _Textrue->GetHeight() * m_Scale.y / 2 + Sprite->GetOffset().y
		, _Textrue->GetWidth() * m_Scale.x
		, _Textrue->GetHeight() * m_Scale.y
		, _Textrue->GetDC()
		, 0, 0
		, _Textrue->GetWidth()
		, _Textrue->GetHeight()
		, m_DeleteColor);
}

void GFlipBookPlayer::Alpha(GTexture*& _Texture)
{
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	GSprite* Sprite = m_CurFlipBook->GetSprite(m_SpriteIdx);

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = m_Alpha;
	blend.AlphaFormat = 0;

	AlphaBlend(hBackDC
		, vPos.x - _Texture->GetWidth() * m_Scale.x / 2  + Sprite->GetOffset().x
		, vPos.y - _Texture->GetHeight() * m_Scale.y / 2 + Sprite->GetOffset().y
		, _Texture->GetWidth() * m_Scale.x
		, _Texture->GetHeight() * m_Scale.y
		, _Texture->GetDC()
		, 0, 0
		, _Texture->GetWidth()
		, _Texture->GetHeight()
		, blend);
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

	// 각종 연산을 위한 임시 텍스쳐
	m_RenderTexture = GAssetManager::GetInst()->CreateTexture(L"Temp", Sprite->GetSlice().x, Sprite->GetSlice().y);

	BitBlt(m_RenderTexture->GetDC()
		, 0
		, 0
		, Sprite->GetSlice().x
		, Sprite->GetSlice().y
		, Sprite->GetAtlas()->GetDC()
		, Sprite->GetLeftTop().x
		, Sprite->GetLeftTop().y
		, SRCCOPY);


	// 반전
	if (m_XFlip)
	{
		XFlip(m_RenderTexture);
		
	}
	if (m_YFlip)
	{
		YFlip(m_RenderTexture);
	}

	// 업애고 싶은 색도 있고 알파값도 수정하고 싶다면
	// 복봍을 여러번 하므로 자제할 것
	if (RGB(-1, -1, -1) != m_DeleteColor && m_Alpha != 255)
	{
		DeleteColorAlpha(m_RenderTexture);
	}
	//없애고 싶은 색만 있다면
	else if (RGB(-1, -1, -1) != m_DeleteColor)
	{
		DeleteColor(m_RenderTexture);
	}
	else if (m_Alpha != 255)
	{
		Alpha(m_RenderTexture);
	}

	GAssetManager::GetInst()->DeleteTexture(m_RenderTexture->GetKey());
}
