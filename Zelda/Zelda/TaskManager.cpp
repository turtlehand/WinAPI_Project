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
		// �θ� ������Ʈ�� ������ ���´�.
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
			
			// �θ� ��ȿ���� �ʴٸ� �ڽ��� ���ӿ� �߰����� �ʰ� ��� �����Ѵ�.
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
			
			// Dead ó���� �� �ȵ� ��쿡�� ó�����ش�.
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
