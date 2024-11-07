#include "pch.h"
#include "GuidedMissile.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CSelectGDI.h"
#include "GCamera.h"

GuidedMissile::GuidedMissile() :
	m_Target(nullptr),
	m_DetectRange(0.f)
{

}

GuidedMissile::~GuidedMissile()
{
}

void GuidedMissile::Tick()
{
	if (IsValid(m_Target))
	{
		TraceTarget_Rotate();
		//TraceTarget_Accel();
	}
	else
		FindTarget();
	

	DrawDebugCircle(PEN_TYPE::GREEN, 0.1f, GetPos(), m_DetectRange);

	GArrow::Tick();
}

void GuidedMissile::FindTarget()
{
	const vector<CObj*>& vecMonster = CLevelMgr::GetInst()->GetCurrentLevel()->GetGameObject(LAYER_TYPE::MONSTER);
	float CurTargetRange = m_DetectRange;
	m_Target = nullptr;

	for (UINT i = 0; i < vecMonster.size(); ++i)
	{
		float TargetRange = (GetPos() - vecMonster[i]->GetPos()).Length();
		if (TargetRange > CurTargetRange || vecMonster[i]->IsDead())
			continue;
		m_Target = vecMonster[i];
		CurTargetRange = TargetRange;
	}

	
}

// 항상 적 방향을 가르킨다.
void GuidedMissile::TraceTarget_Direct()
{
	Vec2 Dir = m_Target->GetPos() - GetPos();
	float Speed = GetVelocity().Length();

	SetVelocity(Dir.Normalize() * Speed);
}

// 적 방향으로 회전한다.
void GuidedMissile::TraceTarget_Rotate()
{
	// 현재 방향
	Vec2 CurDir = GetVelocity().Normalize();
	// 타겟을 향한 방향 벡터
	Vec2 NextDir = (m_Target->GetPos() - GetPos()).Normalize();

	// 내적을 사용하여 sin세타를 구하고 아크코사인을 하여 라디안을 구한다.
	float Radian = acosf(DotProduct(CurDir, NextDir));
	// 라디안을 각도로 변환한다.
	float Degree = Radian * 180.f / PI;
	// 90도에 가까울 수록 속도를 감소시킨다.
	float Scale = Degree / 90.f;
	if (1.f < Scale)
		Scale = 1.f;
	Scale = (1.f - Scale) * 0.5f + 0.5f;
	//SetVelocityScale(Scale);

	// Velocity가 0에 가까워지면 nan이 뜸 ???

	if (!(0.f <= Degree && Degree <= 2.f))
	{
		Vec2 RotateVelocity = Rotate(GetVelocity().Normalize(), PI * CCW(CurDir, NextDir) * DT * 1.f) * GetVelocity().Length();

		SetVelocity(RotateVelocity);
	}

}

// 적 방향으로 가속한다.
void GuidedMissile::TraceTarget_Accel()
{
	Vec2 vDir = m_Target->GetPos() - GetPos();
	vDir = vDir.Normalize();
	//AddForce(vDir * 1000.f);
}

void GuidedMissile::Render()
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
