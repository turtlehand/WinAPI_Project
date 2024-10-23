#include "pch.h"
#include "GSprite.h"

#include "GAssetManager.h"
#include "GPathManager.h"
#include "GTexture.h"

GSprite::GSprite() :
	GAsset(ASSET_TYPE::SPRITE),
	m_Atlas(nullptr),
	m_LeftTop(),
	m_Slice()
{
}

GSprite::~GSprite()
{
}

void GSprite::Create(GTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice)
{
	m_Atlas = _Atlas;
	m_LeftTop = _LeftTop;
	m_Slice = _Slice;
}

int GSprite::Save(const wstring& _RelativePath)
{
	wstring RelativePath = _RelativePath;
	CheckExt(L".sprite", RelativePath);

	// 에셋이 자신이 어디에 저장되는지 알게 함
	SetRelativePath(RelativePath);

	wstring strFilePath = GPathManager::GetContentPath() + RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"w");

	fwprintf_s(File, L"[ASSETTYPE]\n");
	fwprintf_s(File, L"%d\n\n", (int)GetAssetType());

	fwprintf_s(File, L"[KEY]\n");
	fwprintf_s(File, L"%s\n\n",GetKey().c_str());

	fwprintf_s(File, L"[PATH]\n");
	fwprintf_s(File, L"%s\n\n", GetRelativePath().c_str());

	fwprintf_s(File, L"[LEFTTOP]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)GetLeftTop().x, (int)GetLeftTop().y);

	fwprintf_s(File, L"[SLICE]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)GetSlice().x, (int)GetSlice().y);

	fwprintf_s(File, L"[OFFSET]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)GetOffset().x, (int)GetOffset().y);

	fwprintf_s(File, L"[ATLAS]\n");

	fwprintf_s(File, L"[ATLAS_KEY]\n");
	fwprintf_s(File, L"%s\n\n", m_Atlas->GetKey().c_str());

	fwprintf_s(File, L"[ATLAS_PATH]\n");
	fwprintf_s(File, L"%s\n\n", m_Atlas->GetRelativePath().c_str());

	fclose(File);
	return S_OK;
}

int GSprite::Load(const wstring& _RelativePath)
{
	wstring strFilePath = GPathManager::GetContentPath() + _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"r");

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
		else if (szString == L"[LEFTTOP]")
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			SetLeftTop(Vec2(x, y));
		}
		else if (szString == L"[SLICE]")
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			SetSlice(Vec2(x,y));
		}
		else if (szString == L"[OFFSET]")
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			SetOffset(Vec2(x, y));
		}
		else if (szString == L"[ATLAS]")
		{
			wstring AtlasKey, AtlasPath;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasKey = szBuff;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasPath = szBuff;

			m_Atlas = GAssetManager::GetInst()->LoadTexture(AtlasKey, AtlasPath);
		}

	}

	fclose(File);

	return S_OK;
}




