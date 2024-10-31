#include "pch.h"
#include "GTilePalette.h"

#include "GAssetManager.h"
#include "GPathManager.h"
#include "GTile.h"

GTilePalette::GTilePalette() :
	GAsset(ASSET_TYPE::TILEPALETTE),
	m_vecTile{}
{

}

GTilePalette::~GTilePalette()
{

}

int GTilePalette::AddTile(const wstring& Key, const wstring& _FullPath)
{
	GTile* pTile;

	pTile = GAssetManager::GetInst()->LoadTile(Key, _FullPath);

	assert(pTile != nullptr);

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (m_vecTile[i] == pTile)
			return S_OK;
	}

	m_vecTile.push_back(pTile);

	return S_OK;

}

GTile* const GTilePalette::GetTile(Vec2 _MousePos)
{
	return nullptr;
}

int GTilePalette::Save(const wstring& _FullPath)
{
	wstring FullPath = _FullPath;
	CheckExt(L".tp", FullPath);

	// 에셋이 자신이 어디에 저장되는지 알게 함
	SetRelativePath(FullPath);

	FILE* File = nullptr;
	_wfopen_s(&File, FullPath.c_str(), L"w");
	assert(File);

	fwprintf_s(File, L"[ASSETTYPE]\n");
	fwprintf_s(File, L"%d\n\n", (int)GetAssetType());

	fwprintf_s(File, L"[TILESIZE]\n");
	fwprintf_s(File, L"%d\n\n", (int)m_vecTile.size());

	for (int i = 0; i < m_vecTile.size(); ++i)
	{
		fwprintf_s(File, L"[INDEX]\n");
		fwprintf_s(File, L"%d\n\n", i);

		if (m_vecTile[i] == nullptr)
		{
			fwprintf_s(File, L"[KEY]\n");
			fwprintf_s(File, L"%s\n\n", L"NULL");

			fwprintf_s(File, L"[PATH]\n");
			fwprintf_s(File, L"%s\n\n", L"NULL");
		}
		else
		{
			fwprintf_s(File, L"[KEY]\n");
			fwprintf_s(File, L"%s\n\n", m_vecTile[i]->GetKey().c_str());

			fwprintf_s(File, L"[PATH]\n");
			fwprintf_s(File, L"%s\n\n", m_vecTile[i]->GetRelativePath().c_str());
		}
	}

	fclose(File);
	return S_OK;
}

int GTilePalette::Load(const wstring& _FullPath)
{
	wstring strFilePath = _FullPath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"r");
	assert(File);

	while (true)
	{
		wchar_t szBuff[255] = {};
		fwscanf_s(File, L"%s", szBuff, 255);
		wstring szString = szBuff;
		if (szString.empty())
		{
			break;
		}


		if (szString == L"[TILESIZE]")
		{
			int TileSize = 0;
			fwscanf_s(File, L"%d", &TileSize);
			m_vecTile.resize(TileSize);
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

			if (TileKey == L"NULL" || TilePath == L"NULL")
			{
				assert(TileKey == L"NULL" && TilePath == L"NULL");
				m_vecTile[index] = nullptr;
			}
			else
			{
				m_vecTile[index] = GAssetManager::GetInst()->LoadTile(TileKey, TilePath);
			}
		}

	}

	fclose(File);

	return S_OK;
}
