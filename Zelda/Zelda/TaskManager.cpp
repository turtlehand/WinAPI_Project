#include "pch.h"
#include "TaskManager.h"
#include "CObj.h"
#include "CLevelMgr.h"
#include "CLevel.h"

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

void TaskManager::Tick()
{
	for (size_t i = 0; i < m_Garbage.size(); ++i)
	{
		delete m_Garbage[i];
	}
	m_Garbage.clear();

	for (size_t i = 0; i < m_Task.size(); ++i)
	{
		switch (m_Task[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
   			CObj* pObject = (CObj*)m_Task[i].Param0;
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject,(LAYER_TYPE)m_Task[i].Param1);
			pObject->Begin();
		}
			break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			CObj* pObject = (CObj*)m_Task[i].Param0;
			// Dead ó���� �ȵ� ��쿡�� ó�����ش�.
			// ���� ���� ������Ʈ�� ���ؼ� Delete ��û�� �������� ��� ��ó�ϱ� ����
			if (!pObject->IsDead())
			{
				pObject->m_Dead = true;
				m_Garbage.push_back(pObject);
			}
		}
			break;
		case TASK_TYPE::CHANGE_LEVEL:
		{
			CLevelMgr::GetInst()->ChangeLevel((LEVEL_TYPE)m_Task[i].Param0);
		}
			break;
		}
	}
	m_Task.clear();
}
