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
		// 부모 오브젝트와 연결을 끊는다.
		CObj* Parent = m_Garbage[i]->GetParent();
		if (IsValid(Parent))
		{

			m_Garbage[i]->SetParent(nullptr);
		}

		delete m_Garbage[i];
	}
	m_Garbage.clear();

	for (size_t i = 0; i < m_Task.size(); ++i)
	{
		switch (m_Task[i].Type)
		{
		case TASK_TYPE::ACTIVE_OBJECT:
		{
			CObj* pObject = (CObj*)m_Task[i].Param0;
			bool Active = (bool)m_Task[i].Param1;

			if (pObject->m_Active && !Active)
			{
				// 오브젝트가 활성화 된 상태에서 비활성화 할 때
				pObject->m_Active = false;
				pObject->OnDisable();
			}
			else if (!pObject->m_Active && Active)
			{
				// 오브젝트가 비활성화 된 상태에서 활성화 할 때
				pObject->m_Active = true;
				pObject->OnEnable();
			}
		}
		break;
		case TASK_TYPE::CREATE_OBJECT:
		{
   			CObj* pObject = (CObj*)m_Task[i].Param0;
			
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject,(LAYER_TYPE)m_Task[i].Param1);
			pObject->Begin();
		}
		break;

		case TASK_TYPE::CREATE_CHILDE_OBJECT:
		{
			CObj* pParent = (CObj*)m_Task[i].Param0;
			CObj* pObject = (CObj*)m_Task[i].Param1;
			
			// 부모가 유효하지 않다면 자식을 게임에 추가하지 않고 즉시 삭제한다.
			if (!IsValid(pParent))
			{
				DeleteGameObject(pObject);
				break;
			}

			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject, (LAYER_TYPE)m_Task[i].Param2);
			pObject->Begin();
			pParent->AddChild(pObject);
		}
		break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			CObj* pObject = (CObj*)m_Task[i].Param0;
			
			// Dead 처리가 다 안된 경우에만 처리해준다.
			// 동시 같은 오브젝트에 대해서 Delete 요청이 여러번인 경우 대처하기 위함
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
