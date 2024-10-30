#include "pch.h"
#include "GTile.h"

#include "GAssetManager.h"
#include "GPathManager.h"
#include "GSprite.h"

GTile::GTile() :
	GAsset(ASSET_TYPE::TILE),
	m_Sprite(nullptr),
	m_Collider(false)
{
}

GTile::~GTile()
{
}

void GTile::Create(GSprite* _Sprite, bool _Collider)
{
	m_Sprite = _Sprite;
	m_Collider = _Collider;
}

int GTile::Save(const wstring& _RelativePath)
{
	wstring RelativePath = _RelativePath;
	CheckExt(L".tile", RelativePath);

	// 에셋이 자신이 어디에 저장되는지 알게 함
	SetRelativePath(RelativePath);

	wstring strFilePath = GPathManager::GetContentPath() + RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"w");
	assert(File != nullptr);

	fwprintf_s(File, L"[ASSETTYPE]\n");
	fwprintf_s(File, L"%d\n\n", (int)GetAssetType());

	fwprintf_s(File, L"[SPRITE]\n");

	fwprintf_s(File, L"[SPRITE_KEY]\n");
	fwprintf_s(File, L"%s\n\n", m_Sprite->GetKey().c_str());

	fwprintf_s(File, L"[SPRITE_PATH]\n");
	fwprintf_s(File, L"%s\n\n", m_Sprite->GetRelativePath().c_str());

	fclose(File);
	return S_OK;
}

int GTile::Load(const wstring& _RelativePath)
{
	wstring strFilePath = GPathManager::GetContentPath() + _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"r");
	assert(File != nullptr);

	while (true)
	{
		wchar_t szBuff[255] = {};
		fwscanf_s(File, L"%s", szBuff, 255);
		wstring szString = szBuff;
		if (szString.empty())
		{
			break;
		}

		if (szString == L"[SPRITE]")
		{
			wstring AtlasKey, AtlasPath;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasKey = szBuff;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasPath = szBuff;

			m_Sprite = GAssetManager::GetInst()->LoadSprite(AtlasKey, AtlasPath);
		}

	}

	fclose(File);

	return S_OK;
}