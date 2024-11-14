#include "pch.h"
#include "GUI.h"
#include "CSelectGDI.h"
#include "CEngine.h"
#include "GCamera.h"

GUI::GUI() :
	m_MouseHover(false),
	m_LBtnDown(false),
	m_PenType(PEN_TYPE::BLACK),
	m_BrushType(BRUSH_TYPE::WHITE)
{
}

GUI::~GUI()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		delete m_vecChild[i];
	}
	m_vecChild.clear();
}

void GUI::Tick()
{
	MouseHoverCheck();

	Tick_UI();
	
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Tick();
	}
}

void GUI::Tick_UI()
{

}

void GUI::Render()
{
	Render_UI();

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Render();
	}
}

void GUI::Render_UI()
{
	Vec2 vRenderPos = GCamera::GetInst()->GetRenderPos(GetGlobalPos());
	Vec2 vScale = GetScale();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	SELECT_PEN(m_PenType);
	SELECT_BRUSH(m_BrushType);

	Rectangle(dc,
		vRenderPos.x,
		vRenderPos.y,
		vRenderPos.x + vScale.x,
		vRenderPos.y + vScale.y);
}

void GUI::MouseHoverCheck()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vPos = GetGlobalPos();
	Vec2 vScale = GetScale();

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x &&
		vPos.y - vScale.y <= vMousePos.y && vMousePos.y <= vPos.y )
	{
		m_MouseHover = true;
	}
	else
	{
		m_MouseHover = false;
	}
}


