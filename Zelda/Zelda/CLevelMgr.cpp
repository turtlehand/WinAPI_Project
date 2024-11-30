#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"

#include "CLevel.h"
#include "GLevel_Editor.h"
#include "GLevel_Start.h"
#include "GLevel_Stage_0.h"
#include "GLevel_Stage_1.h"
#include "GLevel_Stage_2.h"
#include "GLevel_Stage_3.h"

#include "CollisionManager.h"

#include "GCamera.h"

CLevelMgr::CLevelMgr() :
	m_arrLevel{},
	m_CurLevel(nullptr),
	m_PrevLevelType(LEVEL_TYPE::END),
	m_CurLevelType(LEVEL_TYPE::END)
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
	m_arrLevel[(int)LEVEL_TYPE::STAGE0] = new GLevel_Stage_0;
	m_arrLevel[(int)LEVEL_TYPE::STAGE0]->Awake();
	m_arrLevel[(int)LEVEL_TYPE::STAGE1] = new GLevel_Stage_1;
	m_arrLevel[(int)LEVEL_TYPE::STAGE1]->Awake();
	m_arrLevel[(int)LEVEL_TYPE::STAGE2] = new GLevel_Stage_2;
	m_arrLevel[(int)LEVEL_TYPE::STAGE2]->Awake();
	m_arrLevel[(int)LEVEL_TYPE::STAGE3] = new GLevel_Stage_3;
	m_arrLevel[(int)LEVEL_TYPE::STAGE3]->Awake();

	m_CurLevel = m_arrLevel[(int)LEVEL_TYPE::START];
	m_CurLevelType = LEVEL_TYPE::START;
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
	{
		return;
	}

	// 2. ���� ������ ������Ʈ�� �Ҹ� �����ش�.
	m_CurLevel->End();
	m_PrevLevelType = m_CurLevelType;

	// 3. ���� ������ �����Ϸ��� ������ ��������ش�.
	m_CurLevel = m_arrLevel[(UINT)_Level];
	m_CurLevelType = _Level;

	// 4. ���� ������ Begin�� ȣ�� ��Ų��.
	m_CurLevel->Begin();
	m_CurLevelType = _Level;
}

void CLevelMgr::ReLoadLevel()
{
	m_CurLevel->End();
	m_CurLevel->Begin();
}
