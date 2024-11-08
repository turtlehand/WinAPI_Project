#include "pch.h"
#include "CObj.h"
#include "GComponent.h"
#include "GCollider.h"
#include "GCamera.h"

#include "TaskManager.h"

CObj::CObj() :
	m_Parent(nullptr),
	m_Pos(),
	m_Scale(),
	m_Component(),
	m_LayerType(LAYER_TYPE::END),
	m_PrevActive(true),
	m_Active(true),
	m_Dead(false)
{
}

CObj::~CObj()
{
	Delete_Vector(m_Component);
}

void CObj::FinalTick()
{
	for (size_t i = 0; i < m_Component.size(); ++i)
	{
		m_Component[i]->FinalTick();
	}
}

void CObj::OnCollisionEnter(GCollider* _Collider)
{
}

void CObj::OnCollision(GCollider* _Collider)
{
}

void CObj::OnCollisionExit(GCollider* _Collider)
{
}

void CObj::OnTriggerEnter(GCollider* _Collider)
{
}

void CObj::OnTrigger(GCollider* _Collider)
{
}

void CObj::OnTriggerExit(GCollider* _Collider)
{
}


Vec2 CObj::GetRenderPos()
{
	return GCamera::GetInst()->GetRenderPos(GetGlobalPos());
}

void CObj::SetActive(bool _Active)
{
	Task task = { TASK_TYPE::ACTIVE_OBJECT,(DWORD_PTR)this,(DWORD_PTR)_Active };
	TaskManager::GetInst()->AddTask(task);
}

/// <summary>
/// 부모를 설정한다.
/// </summary>
/// <param name="_Parent"></param>
void CObj::SetParent(CObj* _Parent)
{
	if (m_Parent)
	{
		vector<CObj*>::iterator iter = std::find(m_Parent->m_vecChild.begin(), m_Parent->m_vecChild.end(), this);
		
		assert(iter != m_Parent->m_vecChild.end());

		m_Parent->m_vecChild.erase(iter);
		m_Parent = nullptr;
	}

	m_Parent = _Parent;
	m_Parent->m_vecChild.push_back(this);
}


