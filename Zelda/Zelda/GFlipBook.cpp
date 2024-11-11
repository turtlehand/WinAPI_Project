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

void GFlipBook::ChangeSprite(int index, GSprite* _Sprite)
{
	m_Sprites[index].first = _Sprite;
}

void GFlipBook::ChangeRednerInfo(int index, const RenderInfo& _RenderInfo)
{
	m_Sprites[index].second = _RenderInfo;
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
	assert(File != nullptr);

	fwprintf_s(File, L"[ASSETTYPE]\n");
	fwprintf_s(File, L"%d\n\n", (int)GetAssetType());

	fwprintf_s(File, L"[SPRITESIZE]\n");
	fwprintf_s(File, L"%d\n\n", (int)m_Sprites.size());

	for (int i = 0; i < m_Sprites.size(); ++i)
	{
		fwprintf_s(File, L"[INDEX]\n");
		fwprintf_s(File, L"%d\n\n", i);

		fwprintf_s(File, L"[KEY]\n");
		fwprintf_s(File, L"%s\n\n", m_Sprites[i].first->GetKey().c_str());

		fwprintf_s(File, L"[PATH]\n");
		fwprintf_s(File, L"%s\n\n", m_Sprites[i].first->GetRelativePath().c_str());

		fwprintf_s(File, L"[RENDERINFO]\n");

		fwprintf_s(File, L"[OFFSET]\n");
		fwprintf_s(File, L"%d, %d\n\n", (int)m_Sprites[i].second.Offset.x, (int)m_Sprites[i].second.Offset.y);

		fwprintf_s(File, L"[SCALE]\n");
		fwprintf_s(File, L"%d, %d\n\n", (int)m_Sprites[i].second.Offset.x, (int)m_Sprites[i].second.Offset.y);

		fwprintf_s(File, L"[ALPHA]\n");
		fwprintf_s(File, L"%d\n\n", m_Sprites[i].second.Alpha);

		fwprintf_s(File, L"[COLORREF]\n");
		fwprintf_s(File, L"%d\n\n", m_Sprites[i].second.DeleteColor);

		fwprintf_s(File, L"[XFLIP]\n");
		fwprintf_s(File, L"%d\n\n", m_Sprites[i].second.XFlip ? 1 : 0);

		fwprintf_s(File, L"[YFLIP]\n");
		fwprintf_s(File, L"%d\n\n", m_Sprites[i].second.YFlip ? 1 : 0);
	}

	fclose(File);

	return S_OK;
}

int GFlipBook::Load(const wstring& _RelativePath)
{
	wstring strFilePath = GPathManager::GetContentPath() + _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"r");
	assert(File != nullptr);
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

		if (szString == L"[SPRITESIZE]")
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

			m_Sprites[index].first = GAssetManager::GetInst()->LoadSprite(SpriteKey, SpritePath);

			//RednerInfo
			fwscanf_s(File, L"%s", szBuff,255);

			// Offset
			int x, y;
			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_Sprites[index].second.Offset = Vec2(x, y);

			// Scale
			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_Sprites[index].second.Scale = Vec2(x, y);

			// Alpha
			int Alpha;
			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &Alpha);
			m_Sprites[index].second.Alpha = Alpha;

			// DeleteColor;
			COLORREF DeleteColor;
			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &DeleteColor);
			m_Sprites[index].second.DeleteColor = DeleteColor;

			// XFlip
			int XFlip;
			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &XFlip);
			m_Sprites[index].second.XFlip = XFlip;

			// YFlip
			int YFlip;
			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &YFlip);
			m_Sprites[index].second.YFlip = YFlip;

		}

	}

	fclose(File);

	return S_OK;
}
