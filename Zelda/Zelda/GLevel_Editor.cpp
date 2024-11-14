#include "pch.h"
#include "GLevel_Editor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "GPathManager.h"
#include "CLevelMgr.h"
#include "GAssetManager.h"
#include "GCamera.h"

#include "GUI.h"
#include "GPanel.h"
#include "GButton.h"

#include "GTexture.h"
#include "GTile.h"
#include "GSprite.h"
#include "GTileMap.h"
#include "GTilePalette.h"

#include "GSound.h"


INT_PTR CALLBACK    TileMapInfoProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TextureSliceInfoProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    TilePaletteProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    TileCreateProc(HWND, UINT, WPARAM, LPARAM);

GLevel_Editor::GLevel_Editor() :
	m_hMenu(nullptr),
	m_TilePalette(nullptr),
	m_CurTile(-1),
	m_MapObj(nullptr)
{
}

GLevel_Editor::~GLevel_Editor()
{
}

void GLevel_Editor::Begin()
{
	// ����� ����
	//GSound* pSound = GAssetManager::GetInst()->LoadSound(L"DM_Opening", L"Sound\\DM.wav");

	//if (pSound != nullptr)
	//{
	//	pSound->SetVolume(1.f);
	//	pSound->PlayToBGM(true);

	//}

	// �޴��ٰ� ���ٸ� ���� �ε�
	if (m_hMenu == nullptr)
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPI));
	
	// �޴��ٸ� �����ϰ� â ũ�� ����
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), m_hMenu);
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());

	m_MapObj = new GMap;
	AddObject(m_MapObj, LAYER_TYPE::TILE);
	m_MapObj->SetName(L"Map");
	m_MapObj->GetTileMap()->SetScale(Vec2(4.f, 4.f));

	//m_TilePalette = GAssetManager::GetInst()->LoadTilePalette(L"Forest_Palette", L"TilePalette\\\Forest_Palette.tp");
	//m_MapObj->SetPos(Vec2(-CEngine::GetInst()->GetResolution().x/2, -CEngine::GetInst()->GetResolution().y/2));
	

	/*
	GPanel* pUI = new GPanel;
	AddObject(pUI, LAYER_TYPE::UI);
	pUI->SetName(L"TestUI");
	pUI->SetPos(0, 0);
	pUI->SetScale(200, 400);
	

	GButton* pSaveTMButton = new GButton;
	pUI->AddChildUI(pSaveTMButton);
	pSaveTMButton->SetName(L"TestUI");
	pSaveTMButton->SetPos(10, -360);
	pSaveTMButton->SetScale(80, 30);
	pSaveTMButton->SetBrushType(BRUSH_TYPE::RED);
	pSaveTMButton->AddDelegate(this, (DELEGATE_0)&GLevel_Editor::SaveTileMap);
	

	GButton* pLoadTMButton = new GButton;
	pUI->AddChildUI(pLoadTMButton);
	pLoadTMButton->SetName(L"TestUI");
	pLoadTMButton->SetPos(110, -360);
	pLoadTMButton->SetScale(80, 30);
	pLoadTMButton->SetBrushType(BRUSH_TYPE::BLUE);
	pLoadTMButton->AddDelegate(this, (DELEGATE_0)&GLevel_Editor::LoadTileMap);

	GButton* pLoadTPButton = new GButton;
	pUI->AddChildUI(pLoadTPButton);
	pLoadTPButton->SetName(L"TestUI");
	pLoadTPButton->SetPos(10, -10);
	pLoadTPButton->SetScale(80, 30);
	pLoadTPButton->SetBrushType(BRUSH_TYPE::BLUE);
	pLoadTPButton->AddDelegate(this, (DELEGATE_0)&GLevel_Editor::LoadTilePalette);
	*/

	CLevel::Begin();
}

void GLevel_Editor::Tick()
{
	CLevel::Tick();

	if(GETKEYDOWN(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::START);
	}

	Vec2 CamPos = GCamera::GetInst()->GetOffset();

	if (GETKEYPRESSED(KEY::W))
		GCamera::GetInst()->SetOffset(Vec2(CamPos.x, CamPos.y + DT * 500.f));
	if (GETKEYPRESSED(KEY::S))
		GCamera::GetInst()->SetOffset(Vec2(CamPos.x, CamPos.y - DT * 500.f));
	if (GETKEYPRESSED(KEY::A))
		GCamera::GetInst()->SetOffset(Vec2(CamPos.x - DT * 500.f, CamPos.y));
	if (GETKEYPRESSED(KEY::D))
		GCamera::GetInst()->SetOffset(Vec2(CamPos.x + DT * 500.f, CamPos.y));

	if (m_TilePalette != nullptr)
	{
		if (GETKEYPRESSED(KEY::LBTN))
		{
			if(m_CurTile < 0)
				m_MapObj->GetTileMap()->SetTile(CKeyMgr::GetInst()->GetMousePos(), nullptr);
			else
				m_MapObj->GetTileMap()->SetTile(CKeyMgr::GetInst()->GetMousePos(), m_TilePalette->GetTile(m_CurTile));
		}

		if (GETMW < 0)
		{
			m_CurTile = ++m_CurTile < m_TilePalette->GetTileSize() ? m_CurTile : m_TilePalette->GetTileSize() - 1;
		}
		else if (GETMW > 0)
		{
			m_CurTile = -1 < m_CurTile ? --m_CurTile : -1;
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


	if (m_TilePalette != nullptr && -1 < m_CurTile)
	{
		// ���� Ÿ��
		GTile* Tile = m_TilePalette->GetTile(m_CurTile);
		StretchBlt(CEngine::GetInst()->GetSecondDC(),
			CEngine::GetInst()->GetResolution().x - 100, 50,
			64, 64,
			Tile->GetSprite()->GetAtlas()->GetDC(), Tile->GetSprite()->GetLeftTop().x, Tile->GetSprite()->GetLeftTop().y,
			Tile->GetSprite()->GetSlice().x, Tile->GetSprite()->GetSlice().y, SRCCOPY);
	}


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
	Desc.lpstrFilter = L"TILEMAP\0*.tm\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		wstring RelativePath = szFilePath;
		CheckExt(L".tm", RelativePath);
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
	Desc.lpstrFilter = L"TILEMAP\0*.tm\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		wstring RelativePath = szFilePath;
		CheckExt(L".tm", RelativePath);
		// �� ������Ʈ�� TileMap ������Ʈ ������ �����Ѵ�.
		m_MapObj->GetTileMap()->Load(RelativePath);
	}
}

void GLevel_Editor::SaveTilePalette()
{
	wstring strContentPath = GPathManager::GetContentPath();
	strContentPath += L"TilePalette";

	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// ���������� �� ��θ� �޾Ƴ� ������
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"TP\0*.tp\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		wstring FullPath = szFilePath;
		CheckExt(L".tp", FullPath);
		// �� ������Ʈ�� TileMap ������Ʈ ������ �����Ѵ�.
		m_TilePalette->Save(FullPath);
	}
}

void GLevel_Editor::LoadTilePalette()
{
	wstring strContentPath = GPathManager::GetContentPath();
	strContentPath += L"TilePalette";

	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// ���������� �� ��θ� �޾Ƴ� ������
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"TP\0*.tp\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		wstring FullPath = szFilePath;
		CheckExt(L".tp", FullPath);
		// �� ������Ʈ�� TileMap ������Ʈ ������ �����Ѵ�.
		m_TilePalette = GAssetManager::GetInst()->LoadTilePalette(PathKey(FullPath), FullPath);
		m_CurTile = -1;
	}
}

bool EditorMenu(HINSTANCE _inst, HWND _wnd, int wParam)
{
	switch (wParam)
	{
	case IDM_TILE_SETTING:
	// Ÿ�� ���� �����Ѵ�.
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


	case IDM_TILE_PALETTE:
	// Ÿ�� �ȷ�Ʈ�� ����.
	{
		DialogBox(_inst, MAKEINTRESOURCE(IDD_TILE_PALETTE), _wnd, &TilePaletteProc);

		return true;
	}
	break;
	case IDM_TILE_PALETTE_SAVE:
	{
		// GLevel_Editor�� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� ����� �������־�� ��
		// ���� ������ �˾Ƴ���. ��Ȳ�� ���� ������ �ݵ�� GLevel_Editor���� �Ѵ�.
		CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		GLevel_Editor* EditorLevel = dynamic_cast<GLevel_Editor*>(CurLevel);
		assert(EditorLevel != nullptr);

		EditorLevel->SaveTilePalette();

		return true;
	}
	break;
	case IDM_TILE_PALETTE_LOAD:
	{
		// GLevel_Editor�� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� ����� �������־�� ��
		// ���� ������ �Ȥ��Ƴ���. ��Ȳ�� ���� ������ �ݵ�� GLevel_Editor���� �Ѵ�.
		CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		GLevel_Editor* EditorLevel = dynamic_cast<GLevel_Editor*>(CurLevel);
		assert(EditorLevel != nullptr);

		EditorLevel->LoadTilePalette();

		return true;
	}
	break;
	case IDM_TILE_CREATE:
	// ���ο� Ÿ���� ����
	{
		DialogBox(_inst, MAKEINTRESOURCE(IDD_TILE_CREATE), _wnd, &TileCreateProc);

		return true;
	}
	break;

	case IDM_TEXTURE_SLICE:
	{
		DialogBox(_inst, MAKEINTRESOURCE(IDD_TEXTURE_SLICE), _wnd, &TextureSliceInfoProc);

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

			Vec2 Scale;
			Scale.x = GetDlgItemInt(hDlg, IDC_EDIT_SCALE_X, nullptr, true);
			Scale.y = GetDlgItemInt(hDlg, IDC_EDIT_SCALE_Y, nullptr, true);

			// Ÿ�ϸ��� �����Ų��.
			GMap* pMap = pLevel->GetMapObject();
			pMap->GetComponent<GTileMap>()->SetScale(Scale);
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

// ==========================
// Ÿ�� �ȷ�Ʈ ���ν���
// ==========================
INT_PTR CALLBACK TilePaletteProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		// Ȯ��
		if (LOWORD(wParam) == IDOK)
		{
			
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
		else if (LOWORD(wParam) == IDC_TP_ADD_TILE_BUTTON)
		{
			GLevel_Editor* pLevel = dynamic_cast<GLevel_Editor*>(CLevelMgr::GetInst()->GetCurrentLevel());

			// ������ ���������� �۵��� �� �ְ� ����ó�� ���ش�.
			assert(pLevel != nullptr);
			// Ÿ�� �ȷ�Ʈ�� �������� �ʾҴٸ� ����ó��
			assert(pLevel->GetTilePalette() != nullptr);

			wchar_t buffer[255] = {};
			wstring Key, Path;
			GetDlgItemTextW(hDlg, IDC_TP_ADD_TILE_KEY, buffer, 255);
			Key = buffer;
			GetDlgItemTextW(hDlg, IDC_TP_ADD_TILE_PATH, buffer, 255);
			Path = buffer;
			Path = Path + Key + L".tile";

			pLevel->GetTilePalette()->AddTile(Key, Path);
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_TP_ALT_BUTTON)
		{
			GLevel_Editor* pLevel = dynamic_cast<GLevel_Editor*>(CLevelMgr::GetInst()->GetCurrentLevel());

			// ������ ���������� �۵��� �� �ְ� ����ó�� ���ش�.
			assert(pLevel != nullptr);
			// Ÿ�� �ȷ�Ʈ�� �������� �ʾҴٸ� ����ó��
			assert(pLevel->GetTilePalette() != nullptr);

			wchar_t buffer[255] = {};
			wstring Key, Path;
			GetDlgItemTextW(hDlg, IDC_TP_ALT_KEY, buffer, 255);
			Key = buffer;
			GetDlgItemTextW(hDlg, IDC_TP_ALT_PATH, buffer, 255);
			Path = buffer;

			int StartIndex, Num;
			StartIndex = GetDlgItemInt(hDlg, IDC_TP_ALT_START_INDEX, nullptr, true);
			Num = GetDlgItemInt(hDlg, IDC_TP_ALT_NUM, nullptr, true);

			assert(0 < Num);

			for (int i = StartIndex; i < StartIndex + Num; ++i)
			{
				wstring LKey = Key + L"_" + std::to_wstring(i);
				wstring LPath = Path + Key + L"_" + std::to_wstring(i) + L".tile";

				pLevel->GetTilePalette()->AddTile(LKey, LPath);
			}
			return (INT_PTR)TRUE;
			
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ==========================
// Ÿ�� ���� ���ν���
// ==========================
INT_PTR CALLBACK TileCreateProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		// Ȯ��
		if (LOWORD(wParam) == IDOK)
		{

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
		else if (LOWORD(wParam) == IDC_TC_BUTTON)
		{
			GLevel_Editor* pLevel = dynamic_cast<GLevel_Editor*>(CLevelMgr::GetInst()->GetCurrentLevel());

			// ������ ���������� �۵��� �� �ְ� ����ó�� ���ش�.
			assert(pLevel != nullptr);

			wchar_t buffer[255] = {};
			wstring TileName, TileRelativePath;
			GetDlgItemTextW(hDlg, IDC_TC_NAME, buffer, 255);
			TileName = buffer;
			GetDlgItemTextW(hDlg, IDC_TC_PATH, buffer, 255);
			TileRelativePath = buffer;

			wstring SpriteKey, SpritePath;
			GetDlgItemTextW(hDlg, IDC_TC_SPRITE_KEY, buffer, 255);
			SpriteKey = buffer;
			GetDlgItemTextW(hDlg, IDC_TC_SPRITE_PATH, buffer, 255);
			SpritePath = buffer;

			GSprite* pSprite = GAssetManager::GetInst()->LoadSprite(SpriteKey, SpritePath);
			assert(pSprite != nullptr);

			GAssetManager::GetInst()->CreateTile(TileName, TileRelativePath, pSprite);
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_TLC_BUTTON)
		{
			GLevel_Editor* pLevel = dynamic_cast<GLevel_Editor*>(CLevelMgr::GetInst()->GetCurrentLevel());

			// ������ ���������� �۵��� �� �ְ� ����ó�� ���ش�.
			assert(pLevel != nullptr);

			wchar_t buffer[255] = {};
			wstring TileName, TileRelativePath;
			GetDlgItemTextW(hDlg, IDC_TLC_NAME, buffer, 255);
			TileName = buffer;
			GetDlgItemTextW(hDlg, IDC_TLC_PATH, buffer, 255);
			TileRelativePath = buffer;

			wstring SpriteKey, SpritePath;
			GetDlgItemTextW(hDlg, IDC_TLC_SPRITE_KEY, buffer, 255);
			SpriteKey = buffer;
			GetDlgItemTextW(hDlg, IDC_TLC_SPRITE_PATH, buffer, 255);
			SpritePath = buffer;

			int StartIndex, Num;
			StartIndex = GetDlgItemInt(hDlg, IDC_TLC_SPRITE_START_INDEX, nullptr, true);
			Num = GetDlgItemInt(hDlg, IDC_TLC_SPRITE_NUM, nullptr, true);

			assert(0 < Num);

			for (int i = StartIndex; i < StartIndex + Num; ++i)
			{
				wstring LTKey = TileName + L"_" + std::to_wstring(i);
				wstring LTPath = TileRelativePath + TileName + L"_" + std::to_wstring(i) + L".tile";

				wstring LSKey = SpriteKey + L"_" + std::to_wstring(i);
				wstring LSPath = SpritePath + SpriteKey + L"_" + std::to_wstring(i) + L".sprite";

				GSprite* pSprite = GAssetManager::GetInst()->LoadSprite(LSKey, LSPath);
				assert(pSprite != nullptr);

				GAssetManager::GetInst()->CreateTile(LTKey, LTPath, pSprite);
			}
			return (INT_PTR)TRUE;

		}
		break;
	}
	return (INT_PTR)FALSE;
}


// ==========================
// Texture_Slice Dialog ���ν���
// ==========================
INT_PTR CALLBACK TextureSliceInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		// Ȯ��
		// �ؽ��ĸ� �߶� ��������Ʈ�� �����.
		if (LOWORD(wParam) == IDOK)
		{
			GLevel_Editor* pLevel = dynamic_cast<GLevel_Editor*>(CLevelMgr::GetInst()->GetCurrentLevel());

			// ������ ���������� �۵��� �� �ְ� ����ó�� ���ش�.
			assert(pLevel != nullptr);

			// �ؽ��� �ҷ�����
			wchar_t Buffer[255];
			wstring TexKey, TexPath;
			GetDlgItemTextW(hDlg, IDC_TEXTURE_SLCIE_KEY, Buffer, 255);
			TexKey = Buffer;
			GetDlgItemTextW(hDlg, IDC_TEXTURE_SLCIE_PATH, Buffer, 255);
			TexPath = Buffer;

			GTexture* pTexture = GAssetManager::GetInst()->LoadTexture(TexKey, TexPath);
			// �ؽ��ĸ� ã�� ���ϸ� ����ó��
			assert(pTexture != nullptr);

			// ���� ��ġ
			Vec2 StartPos;
			StartPos.x = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_START_X, nullptr, true);
			StartPos.y = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_START_Y, nullptr, true);

			// ��������Ʈ ũ��
			Vec2 Size;
			Size.x = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_SIZE_X, nullptr, true);
			Size.y = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_SIZE_Y, nullptr, true);

			// ��������Ʈ ƴ
			Vec2 Gap;
			Gap.x = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_GAP_X, nullptr, true);
			Gap.y = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_GAP_Y, nullptr, true);

			// �ڸ� ���
			Vec2 Num;
			Num.x = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_COL, nullptr, true);
			Num.y = GetDlgItemInt(hDlg, IDC_TEXTURE_SLCIE_ROW, nullptr, true);

			for (UINT Row = 0; Row < Num.y; ++Row)
			{
				for (UINT Col = 0; Col < Num.x; ++Col)
				{
					GSprite* pSprite = new GSprite;

					Vec2 LeftTop;
					LeftTop.x = StartPos.x + Size.x * Col + (Col == 0 ? 0 : Gap.x) * Col;
					LeftTop.y = StartPos.y + Size.y * Row + (Row == 0 ? 0 : Gap.y) * Row;

					pSprite->Create(pTexture, LeftTop, Size);

					GetDlgItemTextW(hDlg, IDC_TEXTURE_SLCIE_NAME, Buffer, 255);
					wstring KeyName = Buffer;
					KeyName += L"_";
					KeyName += std::to_wstring(Row * (int)Num.x + Col);
					GAssetManager::GetInst()->AddSprite(KeyName, pSprite);

					wstring strSavePath = L"Sprite\\";
					strSavePath += pSprite->GetKey();
					pSprite->Save(strSavePath);
				}

			}

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