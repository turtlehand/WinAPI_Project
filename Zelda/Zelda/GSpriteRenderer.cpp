#include "pch.h"
#include "GSpriteRenderer.h"

#include "GSprite.h"
#include "GTexture.h"

void GSpriteRenderer::FinalTick()
{
}

void GSpriteRenderer::Render()
{
}

GSpriteRenderer::GSpriteRenderer() :
	GComponent(COMPONENT_TYPE::SPRITERENDERER),
	m_Sprite(nullptr),
	m_Scale(Vec2(1.f,1.f)),
	m_Alpha(255),
	m_DeleteColor(RGB(-1,-1,-1)),
	m_XFlip(false),
	m_YFlip(false)
{
}

GSpriteRenderer::~GSpriteRenderer()
{
	if (nullptr == m_Sprite)
		return;

	// Sprite 를 화면에 그린다.
	HDC hBackDC = CEngine::GetInst()->GetSecondDC();
	Vec2 vPos = GetOwner()->GetRenderPos();

	float StartX = vPos.x - (m_Sprite->GetSlice().x / 2) * m_Scale.x + m_Sprite->GetOffset().x;
	float EndX = StartX = m_Sprite->GetSlice().x * m_Scale.x;

	float StartY = vPos.y - (m_Sprite->GetSlice().y / 2) * m_Scale.x + m_Sprite->GetOffset().y;
	float EndY = m_Sprite->GetSlice().y * m_Scale.y;

	// 반전
	if (m_XFlip)
	{
		float TempX = StartX;
		StartX = EndX;
		EndX = TempX;
	}
	if (m_YFlip)
	{
		float TempY = StartY;
		StartY = EndY;
		EndY = TempY;
	}

	TransparentBlt(hBackDC
		, StartX
		, StartY
		, EndX
		, EndY
		, m_Sprite->GetAtlas()->GetDC()
		, m_Sprite->GetLeftTop().x
		, m_Sprite->GetLeftTop().y
		, m_Sprite->GetSlice().x
		, m_Sprite->GetSlice().y
		, m_DeleteColor);
}
