#include "pch.h"
#include "TaskManager.h"
#include "CObj.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "GComponent.h"

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

void TaskManager::Tick()
{
	for (vector<CObj*>::reverse_iterator iter = m_Garbage.rbegin(); iter != m_Garbage.rend(); ++iter)
	{
		// 부모 오브젝트와 연결을 끊는다.
 		CObj* Object = (*iter);
		CObj* Parent = Object->GetParent();
		if (IsValid(Parent))
		{

			Object->SetParent(nullptr);
		}

		delete Object;
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
		case TASK_TYPE::ENABLED_COMPONENT:
		{
			GComponent* pComponent = (GComponent*)m_Task[i].Param0;
			bool Enabled = (bool)m_Task[i].Param1;

			if (pComponent->m_Enabled && !Enabled)
			{
				// 오브젝트가 활성화 된 상태에서 비활성화 할 때
				pComponent->m_Enabled = false;
			}
			else if (!pComponent->m_Enabled && Enabled)
			{
				// 오브젝트가 비활성화 된 상태에서 활성화 할 때
				pComponent->m_Enabled = true;
			}
		}
		break;
		case TASK_TYPE::CREATE_OBJECT:
		{
   			CObj* pObject = (CObj*)m_Task[i].Param0;
			
			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject,(LAYER_TYPE)m_Task[i].Param1);
		}
		break;

		case TASK_TYPE::CREATE_CHILDE_OBJECT:
		{
			CObj* pParent = (CObj*)m_Task[i].Param0;
			CObj* pObject = (CObj*)m_Task[i].Param1;
			LAYER_TYPE LayerType = (LAYER_TYPE)m_Task[i].Param2;
			
			// 부모가 유효하지 않다면 자식을 게임에 추가하지 않고 즉시 삭제한다.
			if (!IsValid(pParent))
			{
				DeleteGameObject(pObject);
				break;
			}
			// 부모 오브젝트를 삭제 처리하고 자식 오브젝트를 생성하면 자식 오브젝트 삭제되지 않음

			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject, (LAYER_TYPE)m_Task[i].Param2);

			
		}
		break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			// Task가 너무 많아지면 버그가 생기는 듯
			CObj* pObject = (CObj*)m_Task[i].Param0;
			float Time = (float)m_Task[i].Time;

			/*
			// 시간이 아직 남았다면 미뤄준다.
			if (Time > 0.f)
			{
				Time -= DT;
				Task task = { Time, TASK_TYPE::DELETE_OBJECT,(DWORD_PTR)pObject };
				m_TimeTask.push_back(task);
				break;
			}
			*/
			// Dead 처리가 다 안된 경우에만 처리해준다.
			// 동시 같은 오브젝트에 대해서 Delete 요청이 여러번인 경우 대처하기 위함z
			if (!pObject->IsDead())
			{
				list<CObj*> queue;
				queue.push_back(pObject);

				while (!queue.empty())
				{
					CObj* Object = queue.front();
					queue.pop_front();

					for (int i = 0; i < Object->GetChilds().size(); ++i)
					{
						queue.push_back(Object->GetChilds()[i]);
					}

					// 해당 오브젝트가 삭제 상태가 아니라면
					if (IsValid(Object))
					{
						Object->m_Dead = true;
						m_Garbage.push_back(Object);
					}
				}

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

	m_Task = m_TimeTask;
	m_TimeTask.clear();
}
