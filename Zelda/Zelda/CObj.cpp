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
	m_Dead(false),
	m_TitleSprite(nullptr)
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
		// 컴포넌트의 현재와 이전 모두 비활성화 상태라면 
		if (!(m_Component[i]->m_PrevEnabled || m_Component[i]->m_Enabled))
			continue;
		m_Component[i]->FinalTick();
		m_Component[i]->m_PrevEnabled = m_Component[i]->m_Enabled;
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
	Task task = { 0.f, TASK_TYPE::ACTIVE_OBJECT,(DWORD_PTR)this,(DWORD_PTR)_Active };
	TaskManager::GetInst()->AddTask(task);

	// 자식 오브젝트들도 false 시킨다.
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->SetActive(_Active);
	}
}

/// <summary>
/// 부모를 설정한다.
/// </summary>
/// <param name="_Parent"></param>
void CObj::SetParent(CObj* _Parent)
{
	if (IsValid(m_Parent))
	{
		vector<CObj*>::iterator iter = std::find(m_Parent->m_vecChild.begin(), m_Parent->m_vecChild.end(), this);
		
		assert(iter != m_Parent->m_vecChild.end());

		m_Parent->m_vecChild.erase(iter);
		m_Parent = nullptr;
	}

	m_Parent = _Parent;

	if(IsValid(m_Parent))
		m_Parent->m_vecChild.push_back(this);
}


