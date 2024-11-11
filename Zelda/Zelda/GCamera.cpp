#include "pch.h"
#include "GCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CObj.h"

GCamera::GCamera() :
	m_Offset(),
	m_LookAt(),
	m_Diff(),
	m_Target(nullptr)
{

}

GCamera::~GCamera()
{

}

void GCamera::Init()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt + Vec2(m_Offset.x, - m_Offset.y) - (Resolution / 2.f);
}

void GCamera::Tick()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt + Vec2(m_Offset.x, -m_Offset.y) - (Resolution / 2.f);

	if (IsValid(m_Target))
	{
		m_Offset = m_Target->GetPos();
	}

	/*
	if (GETKEYPRESSED(KEY::W))
		m_Offset.y += DT * 500.f;
	if (GETKEYPRESSED(KEY::S))
		m_Offset.y -= DT * 500.f;
	if (GETKEYPRESSED(KEY::A))
		m_Offset.x -= DT * 500.f;
	if (GETKEYPRESSED(KEY::D))
		m_Offset.x += DT * 500.f;
	*/

}

void GCamera::Render()
{
	// 100 격자 그리기
	//for (float i = -50; i < 51; ++i)
	//{
	//	DrawDebugLine(PEN_TYPE::GRAY, 0.f, Vec2(i * 100, -50.f * 100), Vec2(i * 100, 50.f * 100));
	//	DrawDebugLine(PEN_TYPE::GRAY, 0.f, Vec2( -50.f * 100, i * 100), Vec2(50.f * 100, i * 100));
	//}
}



Vec2 GCamera::GetRenderPos(Vec2 _Pos)
{
	Vec2 RenderPos;
	RenderPos.x = _Pos.x - m_Diff.x;
	RenderPos.y = - m_Diff.y - _Pos.y;
	return RenderPos;
}

Vec2 GCamera::GetGamePos(Vec2 _Pos)
{
	Vec2 GamePos;
	GamePos.x = _Pos.x + m_Diff.x;
	GamePos.y = - m_Diff.y - _Pos.y;
	return GamePos;
}
