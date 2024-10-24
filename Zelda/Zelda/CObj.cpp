#include "pch.h"
#include "CObj.h"
#include "GComponent.h"
#include "GCollider.h"
#include "GCamera.h"

CObj::CObj() :
	m_Pos(),
	m_Scale(),
	m_Component(),
	m_LayerType(LAYER_TYPE::END),
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

void CObj::EnterOverlap(GCollider* _Collider)
{
}

void CObj::Overlap(GCollider* _Collider)
{
}

void CObj::ExitOverlap(GCollider* _Collider)
{
}

Vec2 CObj::GetRenderPos() const
{
	return GCamera::GetInst()->GetRenderPos(m_Pos);
}


