#include "pch.h"
#include "GButton.h"

#include "GCamera.h"
#include "CSelectGDI.h"

GButton::GButton() :
	m_Inst(nullptr)
{

}

GButton::~GButton()
{
}


void GButton::Begin()
{

}

void GButton::Tick_UI()
{
	if (IsMouseHover())
	{
		SetPenType(PEN_TYPE::GRAY);
	}
	else
	{
		SetPenType(PEN_TYPE::BLACK);
	}

	if (IsLBtnDown())
	{
		SetBrushType(BRUSH_TYPE::GRAY);
	}
	else
	{
		//SetBrushType(BRUSH_TYPE::WHITE);
	}
}

void GButton::MouseLBtnDown()
{

}

void GButton::MouseLBtnClikced()
{
	if (m_Inst != nullptr && m_MemFunc)
		(m_Inst->*m_MemFunc)();

	//if (m_Inst != nullptr && m_MemFunc)
	//	(m_Inst->*m_MemFunc_1)();

	//if (m_Inst != nullptr && m_MemFunc)
	//	(m_Inst->*m_MemFunc_2)();

}

void GButton::MouseReleased()
{

}

