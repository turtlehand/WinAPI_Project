#include "pch.h"
#include "GGameImage.h"

#include "GSprite.h"
#include "GTexture.h"

#include "GCamera.h"

GGameImage::GGameImage() :
	m_Sprite(nullptr)
{
}

GGameImage::~GGameImage()
{
}

void GGameImage::Awake()
{
}

void GGameImage::Tick_UI()
{

}

void GGameImage::Render_UI()
{
	//GPanel::Render_UI();

	Vec2 vRenderPos = GCamera::GetInst()->GetRenderPos(GetGlobalPos());
	Vec2 vScale = GetScale();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	if (m_Sprite == nullptr)
		return;

	TransparentBlt(CEngine::GetInst()->GetSecondDC(),
		vRenderPos.x - vScale.x/2, vRenderPos.y - vScale.y/2,
		vScale.x, vScale.y,
		m_Sprite->GetAtlas()->GetDC(),
		m_Sprite->GetLeftTop().x, m_Sprite->GetLeftTop().y,
		m_Sprite->GetSlice().x, m_Sprite->GetSlice().y, RGB(116, 116, 116));
}


