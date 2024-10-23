#pragma once
class GCamera
{
	SINGLE(GCamera);
private:
	Vec2	m_LookAt;		// ������ ��ǥ���� ī�޶� �ٶ󺸰� �ִ� ��
	Vec2	m_Offset;		// ���� ��ǥ
	Vec2	m_Diff;			// ī�޶� ���� ������ �ػ� �߾��� ��ġ ���̰�
	CObj*	m_Target;		// ī�޶� Ÿ�� ������Ʈ
public:
	void Init();
	void Tick();
	void Render();

public:

	Vec2 GetLookAt() { return m_LookAt + m_Offset; }

	void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
	Vec2 GetOffset() { return m_Offset; }

	void SetTarget(CObj* _Target) { m_Target = _Target; }

	// Render �� ���
	// ���� ��ǥ�� ������ ��ǥ�� ��ȯ �� �ش�.
	Vec2 GetRenderPos(Vec2 _Pos);

	// ������ ��ǥ�� ���� ��ǥ�� ��ȯ �� �ش�.
	Vec2 GetGamePos(Vec2 _Pos);
};

