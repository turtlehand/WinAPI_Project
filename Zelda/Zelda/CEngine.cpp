#include "pch.h"
#include "CEngine.h"
#include "CSelectGDI.h"
#include "CObj.h"
#include "CLevel.h"

#include "GAssetManager.h"
#include "GPathManager.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "TaskManager.h"
#include "DeBugRenderManager.h"
#include "CollisionManager.h"
#include "GCamera.h"
#include "GUIManager.h"
#include "GSoundManager.h"
#include "GPrefabManager.h"

#include "GTexture.h"

// ���� ������� ����

CEngine::CEngine() :
	m_hInst(nullptr),
	m_hWnd(nullptr),
	m_Resolution{},
	m_hDC(nullptr),
	m_Pen{},
	m_Brush{}
{

}

CEngine::~CEngine()
{
	// DC ����
	ReleaseDC(m_hWnd, m_hDC);

	// SecondBuffer ���� �޸� ����
	//DeleteDC(m_hSecondDC);
	//DeleteObject(m_hSecondBitmap);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	for (UINT i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		if ((BRUSH_TYPE)i == BRUSH_TYPE::HOLLOW)
			continue;
		DeleteObject(m_Brush[i]);
	}

}

HDC CEngine::GetSecondDC()
{
	return m_BackBuffer->GetDC();
}

int CEngine::Init(HINSTANCE _Inst, POINT _Resolution)
{
	m_hInst = _Inst;
	m_Resolution = _Resolution;

	// ��ϵ� �ɼ��� szWindowClass�� Ű�� �Ͽ� �����´�.
	// HWND�� Window�� ID Ÿ��
	// Ŀ�� ������Ʈ ( os �������� �����Ǵ� ��ü )
	m_hWnd = CreateWindowW(L"Key", L"MyGame", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	// ������ ���� ���� �� ���α׷� ���� ����
	if (!m_hWnd)
	{
		// ������ ���� ����
		return E_FAIL;
	}

	ShowWindow(m_hWnd, true);
	UpdateWindow(m_hWnd);

	// ������ ũ�� ����, ��ġ ����
	//SetWindowPos(m_hWnd, nullptr, 10, 10, 1280, 768, 0);
	ChangeWindowSize(m_Resolution);

	// DC ����
	// - Draw ������ --> Window Bitmap
	// - Black Pen
	// - White Brush
	m_hDC = GetDC(m_hWnd);

	// GDIOject ����
	CreateGDIObject();
	CreateSecondBuffer();

	GPathManager::Init();
	GAssetManager::GetInst()->Init();
	GSoundManager::GetInst()->Init();

	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();
	GCamera::GetInst()->Init();

	GPrefabManager::GetInst()->Init();
	

	// ������ ���� ����
	return S_OK;
}

void CEngine::CreateGDIObject()
{
	// Pen
	m_Pen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	m_Pen[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_Pen[(UINT)PEN_TYPE::GRAY] = CreatePen(PS_SOLID, 1, RGB(127, 127, 127));
	m_Pen[(UINT)PEN_TYPE::WHITE] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	// Brush
	m_Brush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));

	m_Brush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_Brush[(UINT)BRUSH_TYPE::BLACK] = CreateSolidBrush(RGB(0, 0, 0));
	m_Brush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(127, 127, 127));
	m_Brush[(UINT)BRUSH_TYPE::WHITE] = CreateSolidBrush(RGB(255, 255, 255));
}



void CEngine::CreateSecondBuffer()
{
	m_BackBuffer = GAssetManager::GetInst()->CreateTexture(L"BackBuffer", (int)m_Resolution.x, (int)m_Resolution.y);
	/*
	// ������ ��Ʈ�ʰ� ������ ũ��(�ػ�) ��Ʈ���� ����
	m_hSecondBitmap = CreateCompatibleBitmap(m_hDC, (int)m_Resolution.x, (int)m_Resolution.y);

	// DC ����
	// Pen : Black
	// Brush : White
	// Bitmap : 1 pixel ��Ʈ��
	
	// m_DC�� ���纻 ����
	m_hSecondDC = CreateCompatibleDC(m_hDC);

	// DC �� Bitmap�� ����Ÿ������ �����ϰ� ������ ����Ű�� ��Ʈ���� ������û
	DeleteObject(SelectObject(m_hSecondDC, m_hSecondBitmap));
	*/
}

void CEngine::ChangeWindowSize(Vec2 _vResolution)
{
	m_Resolution = _vResolution;

	RECT rt = { 0,0,m_Resolution.x, m_Resolution.y };

	// ���� �����찡 Menu �� �ִ��� Ȯ��
	HMENU hMenu = GetMenu(m_hWnd);

	// rt�� �Է��ؾ��ϰ� ������� rt�� ���Եȴ�.
	// Ŭ���̾�Ʈ ũ�⸦ �������� ��ü ������ ũ�⸦ ���� �ϴ� �Լ�(���� ������ ũ��, ������ ��� ��Ÿ��, �޴� ����)
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

	// �������� ��ġ, ũ��, â ũ�� ���� �� ��ġ ���� ����
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

}

void CEngine::Progress()
{
	CTimeMgr::GetInst()->Progress();
	CKeyMgr::GetInst()->Progress();
	DeBugRenderManager::GetInst()->Progress();
	GCamera::GetInst()->Tick();

	// ���� ����
	CLevelMgr::GetInst()->Progress();

	// �浹 �˻� ����
	CollisionManager::GetInst()->Tick();

	GUIManager::GetInst()->Progress();

	// ������
	// ȭ�� ��ü�� �簢������ �׷� �ʱ�ȭ�Ѵ�.
	// ȭ�� Ŭ����
	{
		SELECT_BRUSH(BRUSH_TYPE::GRAY);
		Rectangle(m_BackBuffer->GetDC() , -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
	}

	GCamera::GetInst()->Render();

	// ���� ������
	CLevelMgr::GetInst()->Render();

	// ����� ������
	DeBugRenderManager::GetInst()->Render();

	//CTimeMgr::GetInst()->PrintInfo();
	//TextOut(m_hSecondDC, 0, 20, GPathManager::GetContentPath(), wcslen(GPathManager::GetContentPath()));
	//TextOut(m_hSecondDC, 10, 30, GPathManager::GetBinPath(), wcslen(GPathManager::GetBinPath()));
	//TextOut(m_hSecondDC, 10, 50, GPathManager::GetSolutionPath(), wcslen(GPathManager::GetSolutionPath()));


	// SecondBitmap �ִ� ����� Main
	BitBlt(m_hDC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y, m_BackBuffer->GetDC(), 0, 0, SRCCOPY);

	TaskManager::GetInst()->Tick();
}


