#include "pch.h"
#include "GHeart.h"

#include "GAssetManager.h"
#include "GSprite.h"
#include "GTexture.h"

GHeart::GHeart(const DefaultStatsInfo& _PlayerInfo) :
	m_PlayerInfo(_PlayerInfo),
	m_HeartSprite{nullptr}
{
	m_HeartSprite[0] = GAssetManager::GetInst()->LoadSprite(L"HEART_0", L"Sprite\\UI\\HEART_0.sprite");
	m_HeartSprite[1] = GAssetManager::GetInst()->LoadSprite(L"HEART_1", L"Sprite\\UI\\HEART_1.sprite");
	m_HeartSprite[2] = GAssetManager::GetInst()->LoadSprite(L"HEART_2", L"Sprite\\UI\\HEART_2.sprite");

	SetTitleSprite(m_HeartSprite[2]);
}

GHeart::~GHeart()
{
}

void GHeart::Awake()
{
}

void GHeart::Tick_UI()
{
}

void GHeart::Render_UI()
{
	int MaxHP = m_PlayerInfo.MaxHP / 2;
	int FullHeart = m_PlayerInfo.HP / 2;
	int HaflHeart = m_PlayerInfo.HP % 2;
	int EmptyHeart = (m_PlayerInfo.MaxHP - m_PlayerInfo.HP) / 2;

	Vec2 vPos = GetGlobalPos();
	Vec2 vScale = GetScale();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	int num = 0;

	for (; num < FullHeart; ++num)
	{
		TransparentBlt(CEngine::GetInst()->GetSecondDC(),
			vPos.x + vScale.x * num, vPos.y,
			vScale.x, vScale.y,
			m_HeartSprite[2]->GetAtlas()->GetDC(),
			m_HeartSprite[2]->GetLeftTop().x, m_HeartSprite[2]->GetLeftTop().y,
			m_HeartSprite[2]->GetSlice().x, m_HeartSprite[2]->GetSlice().y, RGB(0, 0, 0));
	}

	for (; num < FullHeart + HaflHeart; ++num)
	{
		TransparentBlt(CEngine::GetInst()->GetSecondDC(),
			vPos.x + vScale.x * num, vPos.y,
			vScale.x, vScale.y,
			m_HeartSprite[1]->GetAtlas()->GetDC(),
			m_HeartSprite[1]->GetLeftTop().x, m_HeartSprite[2]->GetLeftTop().y,
			m_HeartSprite[1]->GetSlice().x, m_HeartSprite[2]->GetSlice().y, RGB(0, 0, 0));
	}

	for (; num < FullHeart + HaflHeart + EmptyHeart; ++num)
	{
		TransparentBlt(CEngine::GetInst()->GetSecondDC(),
			vPos.x + vScale.x * num, vPos.y,
			vScale.x, vScale.y,
			m_HeartSprite[0]->GetAtlas()->GetDC(),
			m_HeartSprite[0]->GetLeftTop().x, m_HeartSprite[2]->GetLeftTop().y,
			m_HeartSprite[0]->GetSlice().x, m_HeartSprite[2]->GetSlice().y, RGB(0, 0, 0));
	}
}


