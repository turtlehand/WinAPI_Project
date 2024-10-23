#include "pch.h"
#include "GPanel.h"

GPanel::GPanel()
{
}

GPanel::~GPanel()
{
}

void GPanel::Begin()
{
}

void GPanel::Tick_UI()
{
	if (IsLBtnDown())
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vDiff = vMousePos - m_DownPos;

		Vec2 vPos = GetPos();
		vPos += vDiff;
		SetPos(vPos);

		m_DownPos = vMousePos;
	}
}

void GPanel::MouseLBtnDown()
{
	m_DownPos = CKeyMgr::GetInst()->GetMousePos();
}

void GPanel::MouseLBtnClikced()
{
}

void GPanel::MouseReleased()
{
}


