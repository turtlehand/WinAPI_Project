#include "pch.h"
#include "CKeyMgr.h"

#include "CEngine.h"
#include "GCamera.h"

UINT KeyValue[(UINT)KEY::KEY_END] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y',
	'A', 'S', 'D', 'F', 'G', 'H',
	'Z', 'X', 'C',  'V',  'B',  'N', 'M',

	VK_RETURN,
	VK_ESCAPE,
	VK_LSHIFT,
	VK_MENU,
	VK_CONTROL,
	VK_SPACE,

	VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	VK_LBUTTON,
	VK_RBUTTON,
};

CKeyMgr::CKeyMgr() :
	m_vecKeyInfo{},
	m_MouseWheel(0),
	m_MousePos()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	m_vecKeyInfo.resize((int)KEY::KEY_END);
	for (UINT i = 0; i < (int)KEY::KEY_END; ++i)
	{
		m_vecKeyInfo[i] = KeyInfo{ KEY_STATE::NONE, false };
	}

	m_MouseWheel = 0;
}

void CKeyMgr::Progress()
{
	if (GetFocus() == CEngine::GetInst()->GetMainWndHwnd())
	{
		for (UINT i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			// 1. 현재 O, 이전 X
			if ((GetAsyncKeyState(KeyValue[i]) & 0x8001) && !m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::DOWN;
				m_vecKeyInfo[i].bPrevPressed = true;
			}
			// 2. 현재 O, 이전 O
			else if ((GetAsyncKeyState(KeyValue[i]) & 0x8001) && m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::PRESSED;
			}
			// 3. 현재 X, 이전 O.
			else if (!(GetAsyncKeyState(KeyValue[i]) & 0x8001) && m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::UP;
				m_vecKeyInfo[i].bPrevPressed = false;
			}
			// 4. 현재 X, 이전 X
			else if (!(GetAsyncKeyState(KeyValue[i]) & 0x8001) && !m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::NONE;
			}

		}

		POINT ptPos = {};

		// 전체 화면 기준으로 마우스의 좌표를 호출한다.
		GetCursorPos(&ptPos);
		// 그 좌표를 창 기준 좌표로 변경시켜준다.
		ScreenToClient(CEngine::GetInst()->GetMainWndHwnd(), &ptPos);

		// 게임 좌표 기준
		// 마우스가 화면 밖이라면 NAN
		m_MousePos = GCamera::GetInst()->GetGamePos(ptPos);
		m_MousePos = IsMouseOffScreen() ? Vec2(NAN, NAN) : GCamera::GetInst()->GetGamePos(ptPos);

		// 화면 좌쵸 기준
		m_MousePos_Window = ptPos;
		m_MousePos_Window = ISMouseOffScreen_Window() ? Vec2(NAN, NAN) : ptPos;

		//
		if (m_MouseWheel != 0 && !m_MouseWheelPrevPressed)
			m_MouseWheelPrevPressed = true;
		else if (m_MouseWheel != 0 && m_MouseWheelPrevPressed)
		{
			m_MouseWheel = 0;
			m_MouseWheelPrevPressed = false;
		}
			

	}
	else
	{
		// 기존 키가 유지되므로 키를 뗀 상태로 변경 시켜준다.
		for (UINT i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			// 이전에 눌렸다면 키를 뗀 상태로 변경
			if (m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::UP;
				m_vecKeyInfo[i].bPrevPressed = false;
			}
			// 키를 뗀 상태라면 해제시켜 줌
			else if (m_vecKeyInfo[i].State == KEY_STATE::UP)
			{
				m_vecKeyInfo[i].State = KEY_STATE::NONE;
			}
		}

		m_MousePos = Vec2(NAN, NAN);
		m_MouseWheel = 0;

	}


}

bool CKeyMgr::IsMouseOffScreen()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution()/2;
	Vec2 CameraPos = GCamera::GetInst()->GetOffset();

	if (CameraPos.x - Resolution.x <= m_MousePos.x && m_MousePos.x <= CameraPos.x + Resolution.x &&
		CameraPos.y - Resolution.y <= m_MousePos.y && m_MousePos.y <= CameraPos.y + Resolution.y)
		return false;

	return true;
}

bool CKeyMgr::ISMouseOffScreen_Window()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution();

	if (0 <= m_MousePos_Window.x && m_MousePos_Window.x <= Resolution.x &&
		0 <= m_MousePos_Window.y && m_MousePos_Window.y <= Resolution.y)
		return false;

	return true;
}
