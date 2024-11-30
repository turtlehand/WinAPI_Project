#pragma once
class GCamera
{
	SINGLE(GCamera);
private:
	Vec2	m_LookAt;		// 윈도우 좌표에서 카메라가 바라보고 있는 곳
	Vec2	m_Offset;		// 게임 좌표
	Vec2	m_Diff;			// 카메라가 보는 지점과 해상도 중앙의 위치 차이값
	CObj*	m_Target;		// 카메라 타겟 오브젝트

	Vec2 m_Center;
	Vec2 m_MapSize;

public:
	void Init();
	void Tick();
	void Render();

public:

	Vec2 GetLookAt() { return m_LookAt + m_Offset; }

	void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
	Vec2 GetOffset() { return m_Offset; }

	void SetTarget(CObj* _Target) { m_Target = _Target; }

	void SetCenter(Vec2 _Center) { m_Center = _Center; }
	void SetMapSize(Vec2 _MapSize);

	// Render 시 사용
	// 게임 좌표를 윈도우 좌표로 변환 해 준다.
	Vec2 GetRenderPos(Vec2 _Pos);

	// 윈도우 좌표를 게임 좌표로 변환 해 준다.
	Vec2 GetGamePos(Vec2 _Pos);

	void LimitCameraArea();
};

