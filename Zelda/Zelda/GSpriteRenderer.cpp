#include "pch.h"
#include "GSpriteRenderer.h"

#include "GAssetManager.h"

#include "GSprite.h"
#include "GTexture.h"

GSpriteRenderer::GSpriteRenderer() :
	GComponent(COMPONENT_TYPE::SPRITERENDERER),
	m_Sprite(nullptr),
	m_Scale(Vec2(1.f, 1.f)),
	m_Alpha(255),
	m_DeleteColor(RGB(-1, -1, -1)),
	m_XFlip(false),
	m_YFlip(false),
	m_RenderTexture(nullptr)
{

}

GSpriteRenderer::~GSpriteRenderer()
{

}

void GSpriteRenderer::XFlip(GTexture*& _Textrue)
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

void GSpriteRenderer::YFlip(GTexture*& _Textrue)
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

void GSpriteRenderer::DeleteColorAlpha(GTexture*& _Textrue)
{
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	GTexture* TempTexture = GAssetManager::GetInst()->CreateTexture(L"DeleteColorAlpha", _Textrue->GetWidth() * m_Scale.x, _Textrue->GetHeight() * m_Scale.y);

	// 임시 텍스쳐에 배경 복사
	BitBlt(TempTexture->GetDC()
		, 0
		, 0
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, hBackDC
		, vPos.x - TempTexture->GetWidth() / 2 + m_Sprite->GetOffset().x
		, vPos.y - TempTexture->GetHeight() / 2 + m_Sprite->GetOffset().y
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
		, vPos.x - TempTexture->GetWidth() / 2 + m_Sprite->GetOffset().x
		, vPos.y - TempTexture->GetHeight() / 2 + m_Sprite->GetOffset().y
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, TempTexture->GetDC()
		, 0, 0
		, TempTexture->GetWidth()
		, TempTexture->GetHeight()
		, blend);

	GAssetManager::GetInst()->DeleteTexture(TempTexture->GetKey());
}

void GSpriteRenderer::DeleteColor(GTexture*& _Textrue)
{
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	// 스프라이트 배경 없애고 텍스쳐에 그리기
	TransparentBlt(hBackDC
		, vPos.x - _Textrue->GetWidth() * m_Scale.x / 2 + m_Sprite->GetOffset().x
		, vPos.y - _Textrue->GetHeight() * m_Scale.y / 2 + m_Sprite->GetOffset().y
		, _Textrue->GetWidth() * m_Scale.x
		, _Textrue->GetHeight() * m_Scale.y
		, _Textrue->GetDC()
		, 0, 0
		, _Textrue->GetWidth()
		, _Textrue->GetHeight()
		, m_DeleteColor);
}

void GSpriteRenderer::Alpha(GTexture*& _Texture)
{
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = m_Alpha;
	blend.AlphaFormat = 0;

	AlphaBlend(hBackDC
		, vPos.x - _Texture->GetWidth() * m_Scale.x / 2 + m_Sprite->GetOffset().x
		, vPos.y - _Texture->GetHeight() * m_Scale.y / 2 + m_Sprite->GetOffset().y
		, _Texture->GetWidth() * m_Scale.x
		, _Texture->GetHeight() * m_Scale.y
		, _Texture->GetDC()
		, 0, 0
		, _Texture->GetWidth()
		, _Texture->GetHeight()
		, blend);
}

void GSpriteRenderer::FinalTick()
{
}

void GSpriteRenderer::Render()
{
	if (nullptr == m_Sprite)
		return;

	// 각종 연산을 위한 임시 텍스쳐
	m_RenderTexture = GAssetManager::GetInst()->CreateTexture(L"Temp", m_Sprite->GetSlice().x, m_Sprite->GetSlice().y);

	BitBlt(m_RenderTexture->GetDC()
		, 0
		, 0
		, m_Sprite->GetSlice().x
		, m_Sprite->GetSlice().y
		, m_Sprite->GetAtlas()->GetDC()
		, m_Sprite->GetLeftTop().x
		, m_Sprite->GetLeftTop().y
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

	// 없애고 싶은 색도 있고 알파값도 수정하고 싶다면
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
