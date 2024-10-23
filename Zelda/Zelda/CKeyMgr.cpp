#include "pch.h"
#include "CKeyMgr.h"

#include "CEngine.h"
#include "GCamera.h"

UINT KeyValue[KEY::KEY_END] =
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

CKeyMgr::CKeyMgr()
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
}

void CKeyMgr::Progress()
{
	if (GetFocus() == CEngine::GetInst()->GetMainWndHwnd())
	{
		for (UINT i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			// 1. ���� O, ���� X
			if ((GetAsyncKeyState(KeyValue[i]) & 0x8001) && !m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::DOWN;
				m_vecKeyInfo[i].bPrevPressed = true;
			}
			// 2. ���� O, ���� O
			else if ((GetAsyncKeyState(KeyValue[i]) & 0x8001) && m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::PRESSED;
			}
			// 3. ���� X, ���� O.
			else if (!(GetAsyncKeyState(KeyValue[i]) & 0x8001) && m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::UP;
				m_vecKeyInfo[i].bPrevPressed = false;
			}
			// 4. ���� X, ���� X
			else if (!(GetAsyncKeyState(KeyValue[i]) & 0x8001) && !m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::NONE;
			}

		}

		POINT ptPos = {};

		// ��ü ȭ�� �������� ���콺�� ��ǥ�� ȣ���Ѵ�.
		GetCursorPos(&ptPos);
		// �� ��ǥ�� â ���� ��ǥ�� ��������ش�.
		ScreenToClient(CEngine::GetInst()->GetMainWndHwnd(), &ptPos);

		// ���콺�� ȭ�� ���̶�� NAN
		m_MousePos = GCamera::GetInst()->GetGamePos(ptPos);
		m_MousePos = IsMouseOffScreen() ? Vec2(NAN, NAN) : GCamera::GetInst()->GetGamePos(ptPos);


	}
	else
	{
		// ���� Ű�� �����ǹǷ� Ű�� �� ���·� ���� �����ش�.
		for (UINT i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			// ������ ���ȴٸ� Ű�� �� ���·� ����
			if (m_vecKeyInfo[i].bPrevPressed)
			{
				m_vecKeyInfo[i].State = KEY_STATE::UP;
				m_vecKeyInfo[i].bPrevPressed = false;
			}
			// Ű�� �� ���¶�� �������� ��
			else if (m_vecKeyInfo[i].State == KEY_STATE::UP)
			{
				m_vecKeyInfo[i].State = KEY_STATE::NONE;
			}
		}

		m_MousePos = Vec2(NAN, NAN);
	}


}

bool CKeyMgr::IsMouseOffScreen()
{
	Vec2 Resolution = CEngine::GetInst()->GetResolution()/2;
	Vec2 CameraPos = GCamera::GetInst()->GetOffset();

	if (CameraPos.x - Resolution.x < m_MousePos.x && m_MousePos.x < CameraPos.x + Resolution.x &&
		CameraPos.y - Resolution.y < m_MousePos.y && m_MousePos.y < CameraPos.y + Resolution.y)
		return false;

	return true;
}