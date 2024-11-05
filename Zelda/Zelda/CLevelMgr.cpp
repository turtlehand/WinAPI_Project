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
	// 1. 현재 레벨과 변경하려는 레벨이 동일하면 아무일도 안 일어난다.
	if (m_CurLevel == m_arrLevel[(UINT)_Level])
		return;

	// 2. 현재 레벨의 오브젝트를 소멸 시켜준다.
	m_CurLevel->End();

	// 3. 현재 레벨을 변경하려는 레벨로 변경시켜준다.
	m_CurLevel = m_arrLevel[(UINT)_Level];

	// 4. 현재 레벨을 Begin을 호출 시킨다.
	m_CurLevel->Begin();
}
