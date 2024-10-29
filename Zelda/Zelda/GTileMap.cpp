#include "pch.h"
#include "GTileMap.h"

#include "GAssetManager.h"
#include "GComponent.h"
#include "GTilePalette.h"

#include "GCamera.h"
#include "GPathManager.h"
#include "GTile.h"
#include "GSprite.h"
#include "GTexture.h"

GTileMap::GTileMap() :
	GComponent(COMPONENT_TYPE::TILEMAP),
	m_Scale(1.f,1.f),
	m_Row(0),
	m_Col(0)
{
}

GTileMap::~GTileMap()
{

}


void GTileMap::SetRowCol(int _Row, int _Col)
{
	m_Row = _Row;
	m_Col = _Col;

	m_vecTile.resize(m_Row * m_Col);

	for (int i = 0; i < m_Row * m_Col; ++i)
	{
		m_vecTile[i] = nullptr;
	}
}

void GTileMap::SetTile(Vec2 _MousePos, GTile* _Tile)
{

	// ȭ���� ����ٸ� ��ȿó��
	if (CKeyMgr::GetInst()->IsMouseOffScreen())
		return;

	// ���콺 ��ǥ�� Object�� ��ǥ�� ���� Offset�� ���Ѵ�. 
	Vec2 Offset = _MousePos - GetOwner()->GetPos();

	// �̷��� ���� Offset�� ������� Ÿ�ϸ��� ��� ���̹Ƿ� ��ȿó���Ѵ�.
	if (Offset.x < 0 || Offset.y < 0)
		return;

	int Row = Offset.y / (TILE_SIZE * m_Scale.y);
	int Col = Offset.x / (TILE_SIZE * m_Scale.x);

	// Row�� Col�� Ÿ�ϸ� ���� ũ�ٸ� ��� ���̹Ƿ� ��ȿó���Ѵ�.
	if (Col < 0 || Row < 0 || m_Col <= Col || m_Row <= Row)
		return;

	// �� Ÿ���� ���� �� 
	if (_Tile == nullptr)
	{
		m_vecTile[Row * m_Col + Col] = nullptr;
		return;
	}
		
	// �������� �ʴ� Ÿ���̶�� ��ȿó��
	assert(GAssetManager::GetInst()->FindTile(_Tile->GetKey()) != nullptr);

	m_vecTile[Row * m_Col + Col] = _Tile;
}

/// <summary>
/// ���콺 ��ġ�� Ÿ���� ��������.
/// </summary>
/// <param name="_MousePos"></param>
/// <returns></returns>
/*
const GTile** GTileMap::GetTile(Vec2 _MousePos)
{
	// ȭ���� ����ٸ� ��ȿó��
	if (CKeyMgr::GetInst()->IsMouseOffScreen())
		return nullptr;

	// ���콺 ��ǥ�� Object�� ��ǥ�� ���� Offset�� ���Ѵ�. 
	Vec2 Offset = _MousePos - GetOwner()->GetPos();

	// �̷��� ���� Offset�� ������� Ÿ�ϸ��� ��� ���̹Ƿ� ��ȿó���Ѵ�.
	if (Offset.x < 0 || Offset.y < 0)
		return nullptr;

	int Row = Offset.y / TILE_SIZE;
	int Col = Offset.x / TILE_SIZE;

	// Row�� Col�� Ÿ�ϸ� ���� ũ�ٸ� ��� ���̹Ƿ� ��ȿó���Ѵ�.
	if (Col < 0 || Row < 0 || m_Col <= Col || m_Row <= Row)
		return nullptr;

	return &m_vecTile[Row * m_Col + Col];
}
*/

int GTileMap::Save(const wstring& _FullPath)
{
	wstring FullPath = _FullPath;
	CheckExt(L".tm", FullPath);

	FILE* File = nullptr;

	_wfopen_s(&File, _FullPath.c_str(), L"w");
	assert(File);

	fwprintf_s(File, L"[ASSETTYPE]\n");
	fwprintf_s(File, L"%s\n\n", L"TILEMAP");

	fwprintf_s(File, L"[ROW]\n");
	fwprintf_s(File, L"%d\n\n", m_Row);

	fwprintf_s(File, L"[COL]\n");
	fwprintf_s(File, L"%d\n\n", m_Col);

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

int GTileMap::Load(const wstring& _FullPath)
{
	wstring FullPath = _FullPath;
	CheckExt(L".tm", FullPath);

	FILE* File = nullptr;

	_wfopen_s(&File, _FullPath.c_str(), L"r");
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

		if (szString == L"[ASSETTYPE]")
		{
			int Row = 0, Col = 0;

			fwscanf_s(File, L"%s", szBuff, 255);		//TILEMAP
			fwscanf_s(File, L"%s", szBuff, 255);		//[ROW]

			fwscanf_s(File, L"%d", &Row);

			fwscanf_s(File, L"%s", szBuff, 255);		//[Col]
			fwscanf_s(File, L"%d", &Col);

			SetRowCol(Row, Col);
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

	return true;
}

void GTileMap::FinalTick()
{
	Vec2 OwnerPos = GetOwner()->GetPos();
	
	for (int i = 0; i < m_Row + 1; ++i)
	{
		DrawDebugLine(PEN_TYPE::GREEN, 0.f,
			OwnerPos + Vec2(0.f, i * TILE_SIZE * m_Scale.y),
			OwnerPos + Vec2(m_Col * TILE_SIZE * m_Scale.x, i * TILE_SIZE * m_Scale.y));
	}

	for (int i = 0; i < m_Col + 1; ++i)
	{
		DrawDebugLine(PEN_TYPE::GREEN, 0.f, 
			OwnerPos + Vec2(i * TILE_SIZE * m_Scale.x, 0.f),
			OwnerPos + Vec2(i * TILE_SIZE * m_Scale.x, m_Row * TILE_SIZE * m_Scale.y));
	}
	

}

void GTileMap::Render()
{
	if (m_vecTile.size() == 0)
		return;

	Vec2 OwnerPos = GetOwner()->GetPos();
	Vec2 OwnerRenderPos = GetOwner()->GetRenderPos();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	int ImgIdx = 0;

	// ����ȭ
	Vec2 vCamLook = GCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// ������ ���� ���� ���� ���ϱ�
	Vec2 RightTop = vCamLook + vResolution / 2 - OwnerPos;
	int MaxRow = (int)(RightTop.y / (TILE_SIZE * m_Scale.y)) + 1;
	int MaxCol = (int)(RightTop.x / (TILE_SIZE * m_Scale.x)) + 1;

	MaxRow = MaxRow <= m_Row ? MaxRow : m_Row;
	MaxCol = MaxCol <= m_Col ? MaxCol : m_Col;

	// ���� �Ʒ��� ���� ���� ���ϱ�
	Vec2 LeftBottom = vCamLook - vResolution / 2 - OwnerPos;
	int MinRow = (int)(LeftBottom.y / (TILE_SIZE * m_Scale.y));
	int MinCol = (int)(LeftBottom.x / (TILE_SIZE * m_Scale.x));

	MinRow = MinRow >= 0 ? MinRow : 0;
	MinCol = MinCol >= 0 ? MinCol : 0;
	

	for (int Row = MinRow; Row < MaxRow; ++Row)
	{
		for (int Col = MinCol; Col < MaxCol; ++Col)
		{

			// �ݸ� ȸ���� �´� ��Ŀ� ���ؼ� �̰� ���° Ÿ���������� 1���� �ε����� ��ȯ
			// �ش� Ÿ�������� �����Ѵ�.
			const GTile* Tile = m_vecTile[Row * m_Col + Col];

			// Ÿ���� ����ִٸ� �׸��� �ʴ´�.
			if (Tile == nullptr)
				continue;

			// �������� �ʴ� Ÿ���̶�� ���Ʈ
			// ���� �ð��� ���� ��Ƹ����Ƿ� ����ȭ �ʿ�
			//assert(GAssetManager::GetInst()->FindTile(Tile->GetKey()) != nullptr);

			StretchBlt(dc,
				(int)OwnerRenderPos.x + Col * TILE_SIZE * m_Scale.x, (int)OwnerRenderPos.y - (Row * TILE_SIZE + TILE_SIZE) * m_Scale.y,
				TILE_SIZE * m_Scale.x, TILE_SIZE * m_Scale.y,
				Tile->GetSprite()->GetAtlas()->GetDC(), Tile->GetSprite()->GetLeftTop().x, Tile->GetSprite()->GetLeftTop().y,
				Tile->GetSprite()->GetSlice().x,Tile->GetSprite()->GetSlice().y, SRCCOPY);
		}
	}
}

