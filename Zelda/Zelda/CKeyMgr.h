#pragma once

// Ű�� ���� ���¸� ��Ÿ���� ������
enum class KEY_STATE
{
	NONE,
	DOWN,
	PRESSED,
	UP,
};

// ����� �� �ִ� Ű�� ��Ÿ���� ������
enum class KEY
{
	Q, W, E, R, T, Y,
	A, S, D, F, G, H,
	Z, X, C, V, B, N, M,

	ENTER,
	ESC,
	LSHIFT,
	ALT,
	CTRL,
	SPACE,

	UP, DOWN, LEFT, RIGHT,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	LBTN,
	RBTN,

	KEY_END,
};


// Ű�� ���� ���� ����, ������ ���ȴ����� �����ϴ� ����ü
struct KeyInfo
{
	KEY_STATE	State;		// ���� ����
	bool bPrevPressed;		// ���� �����ӿ� ���ȴ���
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<KeyInfo>			m_vecKeyInfo;			// Ű�� ������ �����ϴ� �迭
	int						m_MouseWheel;
	bool					m_MouseWheelPrevPressed;
	Vec2					m_MousePos;

public:
	void SetMouseWheel(int _State) { m_MouseWheel = _State; }
	int GetMouseWheel() { return m_MouseWheel; }

	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyInfo[(int) _key].State; }		// Ű�� ���� ���¸� ��ȯ�ϴ� �Լ�
	Vec2 GetMousePos() { return m_MousePos; }

	bool IsMouseOffScreen();
public:
	void Init();
	void Progress();
};

