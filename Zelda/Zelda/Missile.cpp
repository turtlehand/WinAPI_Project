#include "pch.h"
#include "Missile.h"

#include "CSelectGDI.h"
#include "DeBugRenderManager.h"
#include "GCamera.h"

#include"GBoxCollider.h"

Missile::Missile() :
	m_Velocity(),
	m_VelocityScale(1.f),
	m_HitBox(nullptr),
	m_Mass(1.f),
	m_Force()
{
	m_HitBox = AddComponent<GBoxCollider>();
	m_HitBox->SetName(L"Missile_HitBox");
	m_HitBox->SetPos(Vec2(0.f, 0.f));
	m_HitBox->SetScale(Vec2(10.f,10.f));
}

Missile::~Missile()
{
}


void Missile::Begin()
{

}

void Missile::Tick()
{
	// 누적된 힘을 확인한다.
	// 누적된 힘에 의해서 생겨난 가속도를 계산한다.
	// F = M * A
	Vec2 vAccel = m_Force / m_Mass;

	// 가속도에 따른 속도의 변화 적용
	m_Velocity += vAccel * DT ;

	//속도에 따른 이동
	Vec2 vPos = GetPos();
	vPos += m_Velocity * m_VelocityScale * DT;
	SetPos(vPos);

	DrawDebugLine(PEN_TYPE::BLUE, 0.f, GetPos(), GetPos() + m_Velocity * 0.1f);

	// 적용중인 힘 리셋
	m_Force = Vec2(0.f, 0.f);
}


void Missile::Render()
{
	Vec2 vPos = GCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	{
		SELECT_BRUSH(BRUSH_TYPE::BLUE);

		Ellipse(CEngine::GetInst()->GetSecondDC(),
			vPos.x - vScale.x / 2.f,
			vPos.y - vScale.y / 2.f,
			vPos.x + vScale.x / 2.f,
			vPos.y + vScale.y / 2.f);
	}
}

void Missile::EnterOverlap(GCollider* _Collider)
{
	if (_Collider->GetOwner()->GetLayerType() == LAYER_TYPE::MONSTER)
		DeleteGameObject(this);
}

