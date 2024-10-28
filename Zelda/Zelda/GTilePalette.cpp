#include "pch.h"
#include "GTilePalette.h"

#include "GAssetManager.h"
#include "GPathManager.h"
#include "GTile.h"

GTilePalette::GTilePalette() :
	GAsset(ASSET_TYPE::TILEPALETTE),
	m_Tile{}
{

}

GTilePalette::~GTilePalette()
{
}

GTile* const GTilePalette::GetTile(Vec2 _MousePos)
{
	return nullptr;
}

int GTilePalette::Save(const wstring& _RelativePath)
{
	wstring RelativePath = _RelativePath;
	CheckExt(L".tp", RelativePath);

	// 에셋이 자신이 어디에 저장되는지 알게 함
	SetRelativePath(RelativePath);

	wstring strFilePath = GPathManager::GetContentPath() + RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"w");

	fwprintf_s(File, L"[ASSETTYPE]\n");
	fwprintf_s(File, L"%d\n\n", (int)GetAssetType());

	fwprintf_s(File, L"[KEY]\n");
	fwprintf_s(File, L"%s\n\n", GetKey().c_str());

	fwprintf_s(File, L"[PATH]\n");
	fwprintf_s(File, L"%s\n\n", GetRelativePath().c_str());

	fwprintf_s(File, L"[TILESIZE]\n");
	fwprintf_s(File, L"%s\n\n", GetRelativePath().c_str());

	for (int i = 0; i < m_Tile.size(); ++i)
	{
		fwprintf_s(File, L"[INDEX]\n");
		fwprintf_s(File, L"%d\n\n", i);

		fwprintf_s(File, L"[KEY]\n");
		fwprintf_s(File, L"%s\n\n", m_Tile[i]->GetKey().c_str());

		fwprintf_s(File, L"[PATH]\n");
		fwprintf_s(File, L"%s\n\n", m_Tile[i]->GetRelativePath().c_str());
	}

	fclose(File);
	return S_OK;
}

int GTilePalette::Load(const wstring& _RelativePath)
{
	wstring strFilePath = _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"r");

	int SpriteSize = 0;

	while (true)
	{
		wchar_t szBuff[255] = {};
		fwscanf_s(File, L"%s", szBuff, 255);
		wstring szString = szBuff;
		if (szString.empty())
		{
			break;
		}

		if (szString == L"[KEY]")
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			SetKey(szBuff);
		}
		else if (szString == L"[PATH]")
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			SetRelativePath(szBuff);
		}
		else if (szString == L"[TILESIZE]")
		{
			fwscanf_s(File, L"%d", &SpriteSize);
			m_Tile.resize(SpriteSize);
		}
		else if (szString == L"[INDEX]")
		{
			int index = 0;
			fwscanf_s(File, L"%d", &index);

			wstring TileKey, TilePath;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			TileKey = szBuff;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			TilePath = szBuff;

			m_Tile[index] = GAssetManager::GetInst()->LoadTile(TileKey, TilePath);
		}

	}

	fclose(File);

	return S_OK;
}
