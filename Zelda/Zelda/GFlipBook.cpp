#include "pch.h"
#include "GFlipBook.h"


#include "GSprite.h"
#include "GPathManager.h"
#include "GAssetManager.h"


GFlipBook::GFlipBook() :
	GAsset(ASSET_TYPE::FLIPBOOK),
	m_Sprites()
{
}

GFlipBook::~GFlipBook()
{
}

int GFlipBook::Save(const wstring& _RelativePath)
{
	wstring RelativePath = _RelativePath;
	CheckExt(L".flip", RelativePath);

	// 에셋이 자신이 어디에 저장되었는지 알게 함
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

	fwprintf_s(File, L"[SPRITESIZE]\n");
	fwprintf_s(File, L"%d\n\n", (int)m_Sprites.size());

	for (int i = 0; i < m_Sprites.size(); ++i)
	{
		fwprintf_s(File, L"[INDEX]\n");
		fwprintf_s(File, L"%d\n\n", i);

		fwprintf_s(File, L"[KEY]\n");
		fwprintf_s(File, L"%s\n\n", m_Sprites[i]->GetKey().c_str());

		fwprintf_s(File, L"[PATH]\n");
		fwprintf_s(File, L"%s\n\n", m_Sprites[i]->GetRelativePath().c_str());
	}

	fclose(File);

	return S_OK;
}

int GFlipBook::Load(const wstring& _RelativePath)
{
	wstring strFilePath = GPathManager::GetContentPath() + _RelativePath;

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
		else if (szString == L"[SPRITESIZE]")
		{
			fwscanf_s(File, L"%d", &SpriteSize);
			m_Sprites.resize(SpriteSize);
		}
		else if (szString == L"[INDEX]")
		{
			int index = 0;
			fwscanf_s(File, L"%d", &index);

			wstring SpriteKey, SpritePath;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			SpriteKey = szBuff;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			SpritePath = szBuff;

			m_Sprites[index] = GAssetManager::GetInst()->LoadSprite(SpriteKey, SpritePath);
		}

	}

	fclose(File);

	return S_OK;

	return S_OK;
}
