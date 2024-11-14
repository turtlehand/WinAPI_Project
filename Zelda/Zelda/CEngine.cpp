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

// 정적 멤버변수 구현

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
	// DC 해제
	ReleaseDC(m_hWnd, m_hDC);

	// SecondBuffer 관련 메모리 해제
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

	// 등록된 옵션을 szWindowClass를 키로 하여 가져온다.
	// HWND는 Window의 ID 타입
	// 커널 오브젝트 ( os 차원에서 관리되는 객체 )
	m_hWnd = CreateWindowW(L"Key", L"MyGame", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	// 윈도우 생성 실패 시 프로그램 강제 종료
	if (!m_hWnd)
	{
		// 윈도우 생성 실패
		return E_FAIL;
	}

	ShowWindow(m_hWnd, true);
	UpdateWindow(m_hWnd);

	// 윈도우 크기 설정, 위치 설정
	//SetWindowPos(m_hWnd, nullptr, 10, 10, 1280, 768, 0);
	ChangeWindowSize(m_Resolution);

	// DC 생성
	// - Draw 목적지 --> Window Bitmap
	// - Black Pen
	// - White Brush
	m_hDC = GetDC(m_hWnd);

	// GDIOject 생성
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
	

	// 윈도우 생성 성공
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
	// 윈도우 비트맵과 동일한 크기(해상도) 비트맵을 생성
	m_hSecondBitmap = CreateCompatibleBitmap(m_hDC, (int)m_Resolution.x, (int)m_Resolution.y);

	// DC 생성
	// Pen : Black
	// Brush : White
	// Bitmap : 1 pixel 비트맵
	
	// m_DC의 복사본 생성
	m_hSecondDC = CreateCompatibleDC(m_hDC);

	// DC 가 Bitmap을 렌더타켓으로 지정하고 기존에 가리키던 비트맵을 삭제요청
	DeleteObject(SelectObject(m_hSecondDC, m_hSecondBitmap));
	*/
}

void CEngine::ChangeWindowSize(Vec2 _vResolution)
{
	m_Resolution = _vResolution;

	RECT rt = { 0,0,m_Resolution.x, m_Resolution.y };

	// 메인 윈도우가 Menu 가 있는지 확인
	HMENU hMenu = GetMenu(m_hWnd);

	// rt를 입력해야하고 결과값을 rt에 적게된다.
	// 클라이언트 크기를 기준으로 전체 윈도우 크기를 재계산 하는 함수(현재 윈도우 크기, 윈도우 모양 스타일, 메뉴 여부)
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

	// 윈도우의 위치, 크기, 창 크기 조정 및 위치 지정 여부
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

}

void CEngine::Progress()
{
	CTimeMgr::GetInst()->Progress();
	CKeyMgr::GetInst()->Progress();
	DeBugRenderManager::GetInst()->Progress();
	GCamera::GetInst()->Tick();

	// 레벨 진행
	CLevelMgr::GetInst()->Progress();

	// 충돌 검사 실행
	CollisionManager::GetInst()->Tick();

	GUIManager::GetInst()->Progress();

	// 렌더링
	// 화면 전체를 사각형으로 그려 초기화한다.
	// 화면 클리어
	{
		SELECT_BRUSH(BRUSH_TYPE::GRAY);
		Rectangle(m_BackBuffer->GetDC() , -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
	}

	GCamera::GetInst()->Render();

	// 레벨 렌더링
	CLevelMgr::GetInst()->Render();

	// 디버그 렌더링
	DeBugRenderManager::GetInst()->Render();

	//CTimeMgr::GetInst()->PrintInfo();
	//TextOut(m_hSecondDC, 0, 20, GPathManager::GetContentPath(), wcslen(GPathManager::GetContentPath()));
	//TextOut(m_hSecondDC, 10, 30, GPathManager::GetBinPath(), wcslen(GPathManager::GetBinPath()));
	//TextOut(m_hSecondDC, 10, 50, GPathManager::GetSolutionPath(), wcslen(GPathManager::GetSolutionPath()));


	// SecondBitmap 있는 장면을 Main
	BitBlt(m_hDC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y, m_BackBuffer->GetDC(), 0, 0, SRCCOPY);

	TaskManager::GetInst()->Tick();
}


