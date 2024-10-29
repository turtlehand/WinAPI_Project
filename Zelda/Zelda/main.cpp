#include "pch.h"
#include "main.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE	g_hInst = nullptr;
HWND		g_hDlg = nullptr;
// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 프로세스 주소(ID)
	_In_opt_ HINSTANCE hPrevInstance,      // 과거에는 쓰였으나 현재는 안쓰이는 인자이다.
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 옵션을 설정하고 레지스터에 옵션을 등록한다.
	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINAPI);
	wcex.lpszClassName = L"Key";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	if (FAILED(CEngine::GetInst()->Init(hInstance, POINT{ 1024, 768 })))
		return FALSE;
	CTimeMgr::GetInst()->Init();


	// 단축키
	// 단축기 테이블을 가져와서 저장한다.
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

	// 구조체
	MSG msg = {};

	while (true)
	{
		// 메시지큐에 메시지가 존재
		// PM_REMOVE : 확인된 메시지를 제거한다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			// 메시지 처리
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);         // 해석한다.
				DispatchMessage(&msg);          // 처리한다.
			}

		}
		// 메시지큐에 메시지가 없다.
		else
		{
			// 게임 실행
			CEngine::GetInst()->Progress();
		}
	}

	return (int)msg.wParam;
}

bool EditorMenu(HINSTANCE _inst, HWND _wnd, int wParam);

// 메시지를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		if (EditorMenu(g_hInst, hWnd, wmId))
		{
			break;
		}

		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, &About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	case WM_MOUSEMOVE:
		break;
	case WM_SIZE:
		break;
	case WM_SIZING:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEWHEEL:
	{
		if ((SHORT)HIWORD(wParam) > 0)
		{
			CKeyMgr::GetInst()->SetMouseWheel(1);
		}
		else if ((SHORT)HIWORD(wParam) < 0)
		{
			CKeyMgr::GetInst()->SetMouseWheel(-1);
		}
		else
		{
			CKeyMgr::GetInst()->SetMouseWheel(0);
		}
		return 0;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
