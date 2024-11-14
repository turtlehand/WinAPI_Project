#include "pch.h"
#include "GTileMap.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "GAssetManager.h"
#include "GPrefabManager.h"
#include "GComponent.h"
#include "GTilePalette.h"

#include "GCamera.h"
#include "GPathManager.h"
#include "GTile.h"
#include "GSprite.h"
#include "GTexture.h"
#include "DeBugRenderManager.h"

#include "GGrass.h"
#include "GTree.h"
#include "GLog.h"
#include "GRock.h"
#include "GPullRock.h"

#include "GWall.h"

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


void GTileMap::SetScale(Vec2 _Scale)
{
	
	for (size_t i = 0; i < GetOwner()->GetChilds().size(); ++i)
	{
		Vec2 Pos = GetOwner()->GetChilds()[i]->GetPos();

		Pos.x = Pos.x / m_Scale.x * _Scale.x;
		Pos.y = Pos.y / m_Scale.y * _Scale.y;
		GetOwner()->GetChilds()[i]->SetPos(Pos);

	}

	m_Scale = _Scale;

}

void GTileMap::SetRowCol(int _Row, int _Col)
{
	m_Row = _Row;
	m_Col = _Col;

	m_vecTile.resize(m_Row * m_Col);

	for (int i = 0; i < m_Row * m_Col; ++i)
	{
		m_vecTile[i].first = nullptr;
	}
}

void GTileMap::SetTile(Vec2 _MousePos, GTile* _Tile)
{

	// 화면을 벗어났다면 무효처리
	if (CKeyMgr::GetInst()->IsMouseOffScreen())
		return;

	// 마우스 좌표에 Object의 좌표를 빼서 Offset을 구한다. 
	Vec2 Offset = _MousePos - GetOwner()->GetPos();

	// 이렇게 나온 Offset이 음수라면 타일맵을 벗어난 것이므로 무효처리한다.
	if (Offset.x < 0 || Offset.y < 0)
		return;

	int Row = Offset.y / (TILE_SIZE * m_Scale.y);
	int Col = Offset.x / (TILE_SIZE * m_Scale.x);

	// Row와 Col이 타일맵 보다 크다면 벗어난 것이므로 무효처리한다.
	if (Col < 0 || Row < 0 || m_Col <= Col || m_Row <= Row)
		return;

	// 빈 타일을 설정 시 
	if (_Tile == nullptr)
	{
		m_vecTile[Row * m_Col + Col].first = nullptr;
		return;
	}
		
	// 존재하지 않는 타일이라면 무효처리
	assert(GAssetManager::GetInst()->FindTile(_Tile->GetKey()) != nullptr);

	m_vecTile[Row * m_Col + Col].first = _Tile;
}

/// <summary>
/// 마우스 위치에 타일을 내보낸다.
/// </summary>
/// <param name="_MousePos"></param>
/// <returns></returns>
/*
const GTile** GTileMap::GetTile(Vec2 _MousePos)
{
	// 화면을 벗어났다면 무효처리
	if (CKeyMgr::GetInst()->IsMouseOffScreen())
		return nullptr;

	// 마우스 좌표에 Object의 좌표를 빼서 Offset을 구한다. 
	Vec2 Offset = _MousePos - GetOwner()->GetPos();

	// 이렇게 나온 Offset이 음수라면 타일맵을 벗어난 것이므로 무효처리한다.
	if (Offset.x < 0 || Offset.y < 0)
		return nullptr;

	int Row = Offset.y / TILE_SIZE;
	int Col = Offset.x / TILE_SIZE;

	// Row와 Col이 타일맵 보다 크다면 벗어난 것이므로 무효처리한다.
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

		if (m_vecTile[i].first == nullptr)
		{
			fwprintf_s(File, L"[KEY]\n");
			fwprintf_s(File, L"%s\n\n", L"NULL");

			fwprintf_s(File, L"[PATH]\n");
			fwprintf_s(File, L"%s\n\n", L"NULL");
		}
		else
		{
			fwprintf_s(File, L"[KEY]\n");
			fwprintf_s(File, L"%s\n\n", m_vecTile[i].first->GetKey().c_str());

			fwprintf_s(File, L"[PATH]\n");
			fwprintf_s(File, L"%s\n\n", m_vecTile[i].first->GetRelativePath().c_str());
		}

		fwprintf_s(File, L"[CREATUREID]\n");
		fwprintf_s(File, L"%d\n\n", (int)m_vecTile[i].second);

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
				m_vecTile[index].first = nullptr;
			}
			else
			{
				m_vecTile[index].first = GAssetManager::GetInst()->LoadTile(TileKey, TilePath);
			}

			int CreatureID;

			fwscanf_s(File, L"%s", szBuff, 255);
			fwscanf_s(File, L"%d", &CreatureID);
			m_vecTile[index].second = (CREATURE_ID)CreatureID;
		}

	}

	fclose(File);

	CreateCreature();

	return true;
}

void GTileMap::CreateCreature()
{
	CObj* Owner = GetOwner();
	for (size_t i = 0; i < GetOwner()->GetChilds().size(); ++i)
	{
		DeleteGameObject(GetOwner()->GetChilds()[i]);
	}


	for (int Row = 0; Row < m_Row; ++Row)
	{
		for (int Col = 0; Col < m_Col; ++Col)
		{

			// 반목문 회차에 맞는 행렬에 대해서 이게 몇번째 타일정보인지 1차원 인덱스로 변환
			// 해당 타일정보에 접근한다.
			CREATURE_ID CreatureID = m_vecTile[Row * m_Col + Col].second;

			// 타일이 비어있다면 그리지 않는다.
			if (CreatureID == CREATURE_ID::NONE)
				continue;

			// 존재하지 않는 타일이라면 어썰트
			// 은근 시간을 많이 잡아먹으므로 최적화 필요
			//assert(GAssetManager::GetInst()->FindTile(Tile->GetKey()) != nullptr);

			CObj* CreatureObj = GPrefabManager::GetInst()->CreatePrefab(CreatureID);
			LAYER_TYPE LayerType = LAYER_TYPE::END;

			if ((int)CREATURE_ID::Obstacle < (int)CreatureID && (int)CreatureID < (int)CREATURE_ID::Item)
				LayerType = LAYER_TYPE::OBJECT;
			else if ((int)CREATURE_ID::Wall == (int)CreatureID)
				LayerType = LAYER_TYPE::OBJECT;

			if (CreatureObj != nullptr)
			{
				Vec2 Pos;
				Pos.x += m_Scale.x * TILE_SIZE * Col + m_Scale.x * TILE_SIZE/2;
				Pos.y += m_Scale.y * TILE_SIZE * Row + m_Scale.x * TILE_SIZE/2;
				CreatureObj->SetPos(Pos);
				CreateChildGameObject(GetOwner(), CreatureObj, LayerType);
			}
		}
	}
}

void GTileMap::FinalTick()
{
	if (!DeBugRenderManager::GetInst()->GetShow())
		return;

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

	// 최적화
	Vec2 vCamLook = GCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// 오른쪽 위의 열과 행을 구하기
	Vec2 RightTop = vCamLook + vResolution / 2 - OwnerPos;
	int MaxRow = (int)(RightTop.y / (TILE_SIZE * m_Scale.y)) + 1;
	int MaxCol = (int)(RightTop.x / (TILE_SIZE * m_Scale.x)) + 1;

	MaxRow = MaxRow <= m_Row ? MaxRow : m_Row;
	MaxCol = MaxCol <= m_Col ? MaxCol : m_Col;

	// 왼쪽 아래의 열과 행을 구하기
	Vec2 LeftBottom = vCamLook - vResolution / 2 - OwnerPos;
	int MinRow = (int)(LeftBottom.y / (TILE_SIZE * m_Scale.y));
	int MinCol = (int)(LeftBottom.x / (TILE_SIZE * m_Scale.x));

	MinRow = MinRow >= 0 ? MinRow : 0;
	MinCol = MinCol >= 0 ? MinCol : 0;
	

	for (int Row = MinRow; Row < MaxRow; ++Row)
	{
		for (int Col = MinCol; Col < MaxCol; ++Col)
		{

			// 반목문 회차에 맞는 행렬에 대해서 이게 몇번째 타일정보인지 1차원 인덱스로 변환
			// 해당 타일정보에 접근한다.
			const GTile* Tile = m_vecTile[Row * m_Col + Col].first;

			// 타일이 비어있다면 그리지 않는다.
			if (Tile == nullptr)
				continue;

			// 존재하지 않는 타일이라면 어썰트
			// 은근 시간을 많이 잡아먹으므로 최적화 필요
			//assert(GAssetManager::GetInst()->FindTile(Tile->GetKey()) != nullptr);

			StretchBlt(dc,
				(int)OwnerRenderPos.x + Col * TILE_SIZE * m_Scale.x, (int)OwnerRenderPos.y - (Row * TILE_SIZE + TILE_SIZE) * m_Scale.y,
				TILE_SIZE * m_Scale.x, TILE_SIZE * m_Scale.y,
				Tile->GetSprite()->GetAtlas()->GetDC(), Tile->GetSprite()->GetLeftTop().x, Tile->GetSprite()->GetLeftTop().y,
				Tile->GetSprite()->GetSlice().x,Tile->GetSprite()->GetSlice().y, SRCCOPY);
		}
	}
}

