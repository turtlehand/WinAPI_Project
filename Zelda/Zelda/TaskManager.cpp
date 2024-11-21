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
		// �θ� ������Ʈ�� ������ ���´�.
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
				// ������Ʈ�� Ȱ��ȭ �� ���¿��� ��Ȱ��ȭ �� ��
				pObject->m_Active = false;
				pObject->OnDisable();
			}
			else if (!pObject->m_Active && Active)
			{
				// ������Ʈ�� ��Ȱ��ȭ �� ���¿��� Ȱ��ȭ �� ��
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
				// ������Ʈ�� Ȱ��ȭ �� ���¿��� ��Ȱ��ȭ �� ��
				pComponent->m_Enabled = false;
			}
			else if (!pComponent->m_Enabled && Enabled)
			{
				// ������Ʈ�� ��Ȱ��ȭ �� ���¿��� Ȱ��ȭ �� ��
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
			
			// �θ� ��ȿ���� �ʴٸ� �ڽ��� ���ӿ� �߰����� �ʰ� ��� �����Ѵ�.
			if (!IsValid(pParent))
			{
				DeleteGameObject(pObject);
				break;
			}
			// �θ� ������Ʈ�� ���� ó���ϰ� �ڽ� ������Ʈ�� �����ϸ� �ڽ� ������Ʈ �������� ����

			CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObject, (LAYER_TYPE)m_Task[i].Param2);

			
		}
		break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			// Task�� �ʹ� �������� ���װ� ����� ��
			CObj* pObject = (CObj*)m_Task[i].Param0;
			float Time = (float)m_Task[i].Time;

			/*
			// �ð��� ���� ���Ҵٸ� �̷��ش�.
			if (Time > 0.f)
			{
				Time -= DT;
				Task task = { Time, TASK_TYPE::DELETE_OBJECT,(DWORD_PTR)pObject };
				m_TimeTask.push_back(task);
				break;
			}
			*/
			// Dead ó���� �� �ȵ� ��쿡�� ó�����ش�.
			// ���� ���� ������Ʈ�� ���ؼ� Delete ��û�� �������� ��� ��ó�ϱ� ����z
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

					// �ش� ������Ʈ�� ���� ���°� �ƴ϶��
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
