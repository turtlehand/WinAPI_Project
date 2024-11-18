#include "pch.h"
#include "GSlot.h"

#include "GAssetManager.h"
#include "GSprite.h"
#include "GTexture.h"

GSlot::GSlot() :
	m_ItemSprite(nullptr),
	m_BackGroundSprite{ nullptr },
	m_Color(BLUE)
{
	m_BackGroundSprite[BLUE] = GAssetManager::GetInst()->LoadSprite(L"SLOT_BLUE", L"Sprite\\UI\\SLOT_BLUE.sprite");
	m_BackGroundSprite[RED] = GAssetManager::GetInst()->LoadSprite(L"SLOT_RED", L"Sprite\\UI\\SLOT_RED.sprite");
	SetTitleSprite(m_BackGroundSprite[BLUE]);
	SetBrushType(BRUSH_TYPE::GRAY);
}

GSlot::~GSlot()
{
}

void GSlot::Awake()
{
}

void GSlot::Tick_UI()
{
}

void GSlot::Render_UI()
{
	GPanel::Render_UI();

	Vec2 vRenderPos = GetGlobalPos();
	Vec2 vScale = GetScale();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	TransparentBlt(CEngine::GetInst()->GetSecondDC(),
		GetGlobalPos().x, GetGlobalPos().y,
		vScale.x, vScale.y,
		m_BackGroundSprite[m_Color]->GetAtlas()->GetDC(),
		m_BackGroundSprite[m_Color]->GetLeftTop().x, m_BackGroundSprite[m_Color]->GetLeftTop().y,
		m_BackGroundSprite[m_Color]->GetSlice().x, m_BackGroundSprite[m_Color]->GetSlice().y, RGB(116,116,116));

	if (m_ItemSprite == nullptr)
		return;

	TransparentBlt(CEngine::GetInst()->GetSecondDC(),
		GetGlobalPos().x + vScale.x * 0.125f, GetGlobalPos().y + vScale.y * 0.125f,
		vScale.x * 0.75f, vScale.y * 0.75f,
		m_ItemSprite->GetAtlas()->GetDC(),
		m_ItemSprite->GetLeftTop().x, m_ItemSprite->GetLeftTop().y,
		m_ItemSprite->GetSlice().x, m_ItemSprite->GetSlice().y, RGB(116, 116, 116));
}

