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
	m_CurFlipBookIndex(-1),
	m_SpriteIdx(0),
	m_FPS(0.f),
	m_Time(0.f),
	m_Repeat(true),
	m_Play(false),
	m_Finish(false),

	m_RenderTexture(nullptr),
	/*
	m_Scale(1.f, 1.f),
	m_Alpha(255),
	m_DeleteColor(RGB(-1, -1, -1)),
	*/
	m_XFlip(false),
	m_YFlip(false),
	m_Alpha(255)
{
}

GFlipBookPlayer::~GFlipBookPlayer()
{
}

void GFlipBookPlayer::XFlip(GTexture*& _Textrue)
{
	// ���ο� �ؽ��ĸ� �����ϰ�
	// �� �ؽ��Ŀ� ������ ���� �ؽ��ĸ� �����Ѵ�.
	// ���� �ؽ��Ĵ� ����������.
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
	// ���ο� �ؽ��ĸ� �����ϰ�
	// �� �ؽ��Ŀ� ������ ���� �ؽ��ĸ� �����Ѵ�.
	// ���� �ؽ��Ĵ� ����������.
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

	GSprite* Sprite = m_vecFlipBook[m_CurFlipBookIndex]->GetSprite(m_SpriteIdx);
	RenderInfo& Info = m_vecFlipBook[m_CurFlipBookIndex]->GetRenderInfo(m_SpriteIdx);

	GTexture* TempTexture = GAssetManager::GetInst()->CreateTexture(L"DeleteColorAlpha", _Textrue->GetWidth() * Info.Scale.x, _Textrue->GetHeight() * Info.Scale.y);

	// �ӽ� �ؽ��Ŀ� ��� ����
	BitBlt(TempTexture->GetDC()
		, 0
		, 0
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, hBackDC
		, vPos.x - TempTexture->GetWidth() / 2 + Sprite->GetOffset().x
		, vPos.y - TempTexture->GetHeight() / 2 + Sprite->GetOffset().y
		, SRCCOPY);

	// ��������Ʈ ��� ���ְ� �ؽ��Ŀ� �׸���
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
		, Info.DeleteColor);

	// �ؽ��ĸ� ��濡 �������ϰ� �׸���
	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = Info.Alpha * (m_Alpha / 255 );
	blend.AlphaFormat = 0;

	AlphaBlend(hBackDC
		, vPos.x - TempTexture->GetWidth() / 2 + Sprite->GetOffset().x * Info.Scale.x + (m_XFlip != Info.XFlip ? - Info.Offset.x * Info.Scale.x : Info.Offset.x * Info.Scale.x)
		, vPos.y - TempTexture->GetHeight() / 2 + Sprite->GetOffset().y * Info.Scale.y + (m_YFlip != Info.YFlip ? Info.Offset.y * Info.Scale.y : - Info.Offset.y * Info.Scale.y)
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

	GSprite* Sprite = m_vecFlipBook[m_CurFlipBookIndex]->GetSprite(m_SpriteIdx);
	RenderInfo& Info = m_vecFlipBook[m_CurFlipBookIndex]->GetRenderInfo(m_SpriteIdx);

	// ��������Ʈ ��� ���ְ� �ؽ��Ŀ� �׸���
	TransparentBlt(hBackDC
		, vPos.x - _Textrue->GetWidth() * Info.Scale.x / 2 + Sprite->GetOffset().x * Info.Scale.x + (m_XFlip != Info.XFlip ? -Info.Offset.x * Info.Scale.x : Info.Offset.x * Info.Scale.x)
		, vPos.y - _Textrue->GetHeight() * Info.Scale.y / 2 + Sprite->GetOffset().y * Info.Scale.y + (m_YFlip != Info.YFlip ? Info.Offset.y * Info.Scale.y : -Info.Offset.y * Info.Scale.y)
		, _Textrue->GetWidth() * Info.Scale.x
		, _Textrue->GetHeight() * Info.Scale.y
		, _Textrue->GetDC()
		, 0, 0
		, _Textrue->GetWidth()
		, _Textrue->GetHeight()
		, Info.DeleteColor);
}

void GFlipBookPlayer::Alpha(GTexture*& _Texture)
{
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	GSprite* Sprite = m_vecFlipBook[m_CurFlipBookIndex]->GetSprite(m_SpriteIdx);
	RenderInfo& Info = m_vecFlipBook[m_CurFlipBookIndex]->GetRenderInfo(m_SpriteIdx);

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = Info.Alpha * (m_Alpha / 255);
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(hBackDC
		, vPos.x - _Texture->GetWidth() * Info.Scale.x / 2  + Sprite->GetOffset().x * Info.Scale.x + (m_XFlip != Info.XFlip ? -Info.Offset.x * Info.Scale.x : Info.Offset.x * Info.Scale.x)
		, vPos.y - _Texture->GetHeight() * Info.Scale.y / 2 + Sprite->GetOffset().y * Info.Scale.y + (m_YFlip != Info.YFlip ? Info.Offset.y * Info.Scale.y : -Info.Offset.y * Info.Scale.y)
		, _Texture->GetWidth() * Info.Scale.x
		, _Texture->GetHeight() * Info.Scale.y
		, _Texture->GetDC()
		, 0, 0
		, _Texture->GetWidth()
		, _Texture->GetHeight()
		, blend);
}

void GFlipBookPlayer::FinalTick()
{
	wstring Name = GetOwner()->GetName();
	//���� ������� FlipBook�� ������ ��
	if (-1 == m_CurFlipBookIndex)
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

	if (m_Play)
	{
		m_Time += DT;
		if (1.f / m_FPS <= m_Time)
		{
			m_Time -= 1.f / m_FPS;
			++m_SpriteIdx;

			// ������ Sprite�� �����ߴٸ�
			if (m_vecFlipBook[m_CurFlipBookIndex]->GetMaxSpriteCount() <= m_SpriteIdx)
			{
				m_Finish = true;
				--m_SpriteIdx;
			}
		}
	}
	
}

void GFlipBookPlayer::Render()
{
	if (-1 == m_CurFlipBookIndex)
		return;

	GSprite* Sprite = m_vecFlipBook[m_CurFlipBookIndex]->GetSprite(m_SpriteIdx);
	RenderInfo& Info = m_vecFlipBook[m_CurFlipBookIndex]->GetRenderInfo(m_SpriteIdx);

	// ���� ������ ���� �ӽ� �ؽ���
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


	// ����
	if (m_XFlip != Info.XFlip)
	{
		XFlip(m_RenderTexture);
		
	}
	if (m_YFlip != Info.YFlip)
	{
		YFlip(m_RenderTexture);
	}

	// ���ְ� ���� ���� �ְ� ���İ��� �����ϰ� �ʹٸ�
	// ���L�� ������ �ϹǷ� ������ ��
	if (RGB(-1, -1, -1) != Info.DeleteColor && (Info.Alpha != 255 || m_Alpha != 255))
	{
		DeleteColorAlpha(m_RenderTexture);
	}
	// ���ְ� ���� ���� �ִٸ�
	else if (RGB(-1, -1, -1) != Info.DeleteColor)
	{
		DeleteColor(m_RenderTexture);
	}
	// ���İ��� �����ϰ� �ʹٸ�
	else
	{
		Alpha(m_RenderTexture);
	}

	GAssetManager::GetInst()->DeleteTexture(m_RenderTexture->GetKey());
}
