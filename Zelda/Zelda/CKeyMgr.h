#pragma once

// 키의 현재 상태를 나타내는 열거형
enum class KEY_STATE
{
	NONE,
	DOWN,
	PRESSED,
	UP,
};

// 사용할 수 있는 키를 나타내는 열거형
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


// 키의 정보 현재 상태, 이전에 눌렸는지를 저장하는 구조체
struct KeyInfo
{
	KEY_STATE	State;		// 현재 상태
	bool bPrevPressed;		// 이전 프레임에 눌렸는지
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<KeyInfo>			m_vecKeyInfo;			// 키의 정보를 저장하는 배열
	int						m_MouseWheel;
	bool					m_MouseWheelPrevPressed;
	Vec2					m_MousePos;

public:
	void SetMouseWheel(int _State) { m_MouseWheel = _State; }
	int GetMouseWheel() { return m_MouseWheel; }

	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyInfo[(int) _key].State; }		// 키의 현재 상태를 반환하는 함수
	Vec2 GetMousePos() { return m_MousePos; }

	bool IsMouseOffScreen();
public:
	void Init();
	void Progress();
};

