#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"

#include "CLevel.h"
#include "GLevel_Editor.h"
#include "GLevel_Start.h"

#include "CollisionManager.h"

#include "GCamera.h"

CLevelMgr::CLevelMgr() :
	m_arrLevel{},
	m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	Delete_Array(m_arrLevel);
}

void CLevelMgr::Init()
{
	m_arrLevel[(int)LEVEL_TYPE::EDITOR] = new GLevel_Editor;
	m_arrLevel[(int)LEVEL_TYPE::EDITOR]->Awake();
	m_arrLevel[(int)LEVEL_TYPE::START] = new GLevel_Start;
	m_arrLevel[(int)LEVEL_TYPE::START]->Awake();

	m_CurLevel = m_arrLevel[(int)LEVEL_TYPE::START];
	m_CurLevel->Begin();
}

void CLevelMgr::Progress()
{
	if (m_CurLevel == nullptr)
		return;

	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}

void CLevelMgr::Render()
{
	m_CurLevel->Render();
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _Level)
{
	// 1. ���� ������ �����Ϸ��� ������ �����ϸ� �ƹ��ϵ� �� �Ͼ��.
	if (m_CurLevel == m_arrLevel[(UINT)_Level])
		return;

	// 2. ���� ������ ������Ʈ�� �Ҹ� �����ش�.
	m_CurLevel->End();

	// 3. ���� ������ �����Ϸ��� ������ ��������ش�.
	m_CurLevel = m_arrLevel[(UINT)_Level];

	// 4. ���� ������ Begin�� ȣ�� ��Ų��.
	m_CurLevel->Begin();
}
