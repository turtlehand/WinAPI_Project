#include "pch.h"
#include "GLevel_Editor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "GPathManager.h"
#include "CLevelMgr.h"
#include "GAssetManager.h"

#include "GUI.h"
#include "GPanel.h"
#include "GButton.h"
#include "GTileMap.h"

#include "GSound.h"


INT_PTR CALLBACK    TileMapInfoProc(HWND, UINT, WPARAM, LPARAM);

GLevel_Editor::GLevel_Editor() :
	m_hMenu(nullptr),
	m_MapObj(nullptr)
{
}

GLevel_Editor::~GLevel_Editor()
{
}

void GLevel_Editor::Begin()
{
	// ����� ����
	GSound* pSound = GAssetManager::GetInst()->LoadSound(L"DM_Opening", L"Sound\\DM.wav");

	if (pSound != nullptr)
	{
		pSound->SetVolume(1.f);
		pSound->PlayToBGM(true);

	}

	// �޴��ٰ� ���ٸ� ���� �ε�
	if (m_hMenu == nullptr)
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPI));
	
	// �޴��ٸ� �����ϰ� â ũ�� ����
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), m_hMenu);
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());

	m_MapObj = new GMap;
	AddObject(m_MapObj, LAYER_TYPE::TILE);
	m_MapObj->SetName(L"Map");
	m_MapObj->GetTileMap()->SetAtlasTexture(GAssetManager::GetInst()->LoadTexture(L"Tile", L"Texture\\TILE.bmp"));
	//m_MapObj->SetPos(Vec2(-CEngine::GetInst()->GetResolution().x/2, -CEngine::GetInst()->GetResolution().y/2));
	

	GPanel* pUI = new GPanel;
	AddObject(pUI, LAYER_TYPE::UI);
	pUI->SetName(L"TestUI");
	pUI->SetPos(0, 0);
	pUI->SetScale(200, 400);
	

	GButton* pSaveButton = new GButton;
	pUI->AddChildUI(pSaveButton);
	pSaveButton->SetName(L"TestUI");
	pSaveButton->SetPos(10, -10);
	pSaveButton->SetScale(80, 30);
	pSaveButton->SetBrushType(BRUSH_TYPE::RED);
	pSaveButton->AddDelegate(this, (DELEGATE_0)&GLevel_Editor::SaveTileMap);
	

	GButton* pLoadButton = new GButton;
	pUI->AddChildUI(pLoadButton);
	pLoadButton->SetName(L"TestUI");
	pLoadButton->SetPos(110, -10);
	pLoadButton->SetScale(80, 30);
	pLoadButton->SetBrushType(BRUSH_TYPE::BLUE);
	pLoadButton->AddDelegate(this, (DELEGATE_0)&GLevel_Editor::LoadTileMap);
	

	CLevel::Begin();
}

void GLevel_Editor::Tick()
{
	CLevel::Tick();

	if(GETKEYDOWN(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

	if (GETKEYPRESSED(KEY::LBTN))
	{
		Tile* TileInfo = m_MapObj->GetTileMap()->GetTile(CKeyMgr::GetInst()->GetMousePos());
		if (TileInfo != nullptr)
		{
			TileInfo->ImgIdx = 5;
		}
	}

}

void GLevel_Editor::Render()
{
	CLevel::Render();

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Editor Level", wcslen(L"Editor Level"));

	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos();
	wchar_t buff[255] = {};
	swprintf_s(buff, 255, L"%d, %d", (int)MousePos.x, (int)MousePos.y);
	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 30, buff, wcslen(buff));

}

void GLevel_Editor::End()
{
	CLevel::End();

	// �޴��ٸ� ������ �ʰ��ϰ� â ũ�� ������
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), nullptr);
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());
}

void GLevel_Editor::SaveTileMap()
{

	wstring strContentPath = GPathManager::GetContentPath();
	strContentPath += L"TileMap";


	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// ���������� �� ��θ� �޾Ƴ� ������
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		wstring RelativePath = szFilePath;
		CheckExt(L".tile", RelativePath);
		// �� ������Ʈ�� TileMap ������Ʈ ������ �����Ѵ�.
		m_MapObj->GetTileMap()->Save(RelativePath);
	}
}

void GLevel_Editor::LoadTileMap()
{
	wstring strContentPath = GPathManager::GetContentPath();
	strContentPath += L"TileMap";


	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// ���������� �� ��θ� �޾Ƴ� ������
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		wstring RelativePath = szFilePath;
		CheckExt(L".tile", RelativePath);
		// �� ������Ʈ�� TileMap ������Ʈ ������ �����Ѵ�.
		m_MapObj->GetTileMap()->Load(RelativePath);
	}
}

bool EditorMenu(HINSTANCE _inst, HWND _wnd, int wParam)
{
	switch (wParam)
	{
	case IDM_TILE_SETTING:
	{
		DialogBox(_inst, MAKEINTRESOURCE(IDD_TILE_SETTING), _wnd, &TileMapInfoProc);

		return true;
	}
	break;
	case IDM_TILE_SAVE:
	{
		// GLevel_Editor�� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� ����� �������־�� ��
		// ���� ������ �Ȥ��Ƴ���. ��Ȳ�� ���� ������ �ݵ�� GLevel_Editor���� �Ѵ�.
		CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		GLevel_Editor* EditorLevel = dynamic_cast<GLevel_Editor*>(CurLevel);
		assert(EditorLevel != nullptr);

		EditorLevel->SaveTileMap();

		return true;
	}
	break;
	case IDM_TILE_LOAD:
	{
		// GLevel_Editor�� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� ����� �������־�� ��
		// ���� ������ �Ȥ��Ƴ���. ��Ȳ�� ���� ������ �ݵ�� GLevel_Editor���� �Ѵ�.
		CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		GLevel_Editor* EditorLevel = dynamic_cast<GLevel_Editor*>(CurLevel);
		assert(EditorLevel != nullptr);

		EditorLevel->LoadTileMap();
		return true;
	}
	break;
	}

	return false;
}

// ==========================
// Tile_Map_Info Dialog ���ν���
// ==========================
INT_PTR CALLBACK TileMapInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		// Ȯ��
		// Row, Col ���� �������� Ÿ�ϸ��� �����Ų��.
		if (LOWORD(wParam) == IDOK)
		{
			GLevel_Editor* pLevel = dynamic_cast<GLevel_Editor*>(CLevelMgr::GetInst()->GetCurrentLevel());

			// ������ ���������� �۵��� �� �ְ� ����ó�� ���ش�.
			assert(pLevel != nullptr);

			// �ش� ID�� �������� �����´�.
			int Row = GetDlgItemInt(hDlg, IDC_EDIT_ROW, nullptr, true);
			int Col = GetDlgItemInt(hDlg, IDC_EDIT_COL, nullptr, true);

			// Ÿ�ϸ��� �����Ų��.
			GMap* pMap = pLevel->GetMapObject();
			pMap->GetComponent<GTileMap>()->SetRowCol(Row, Col);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		// ���
		// �ƹ��ϵ� �Ͼ�� �ʴ´�.
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
