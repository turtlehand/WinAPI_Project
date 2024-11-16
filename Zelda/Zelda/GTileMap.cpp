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
#include "GBoxCollider.h"

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
	m_vecCreature.resize(m_Row * m_Col);

	for (int i = 0; i < m_Row * m_Col; ++i)
	{
		m_vecTile[i].first = nullptr;
		m_vecTile[i].second = CREATURE_ID::NONE;
		m_vecCreature[i] = nullptr;
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
		m_vecTile[Row * m_Col + Col].first = nullptr;
		return;
	}
		
	// �������� �ʴ� Ÿ���̶�� ��ȿó��
	assert(GAssetManager::GetInst()->FindTile(_Tile->GetKey()) != nullptr);

	m_vecTile[Row * m_Col + Col].first = _Tile;
}

void GTileMap::SetCreature(Vec2 _MousePos, CREATURE_ID _CreatureID)
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
	if (_CreatureID == CREATURE_ID::NONE)
	{
		m_vecTile[Row * m_Col + Col].second = CREATURE_ID::NONE;
		CreatCreature_Pos(_CreatureID, Row, Col);
		return;
	}

	// �������� �ʴ� Ÿ���̶�� ��ȿó��
	assert(GPrefabManager::GetInst()->FindPrefab(_CreatureID) != nullptr);

	m_vecTile[Row * m_Col + Col].second = _CreatureID;

	CreatCreature_Pos(_CreatureID, Row, Col);
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


void GTileMap::Optimize()
{
	vector<int> DArray(m_Row * m_Col, 0);
	int num = 1;

	for (int Row = 0; Row < m_Row; ++Row)
	{
		for (int Col = 0; Col < m_Col; ++Col)
		{
			if (DArray[Row * m_Col + Col] != 0 || m_vecTile[Row * m_Col + Col].second != CREATURE_ID::Wall)
				continue;

			Vec2 LeftDown = Vec2(Col, Row);
			Vec2 RightTop = Vec2(Col, Row);

			while (true)
			{
				int rt = (RightTop.y + 1) * m_Col + RightTop.x + 1;
				int r = RightTop.y * m_Col + RightTop.x + 1;
				int t = (RightTop.y + 1) * m_Col + RightTop.x;

				// ������ �� ���� ���� �Ѵٸ� 
				if (RightTop.x + 1 < m_Col && RightTop.y + 1 < m_Row && m_vecTile[rt].second == CREATURE_ID::Wall && DArray[rt] == 0)
				{
					// ������, �� �� ��� Ȯ��
					// ������ �� ��� Ȯ��
					bool ROK = true;
					// ������ ���� �Ʒ��� ��� �����ϴ� �� Ȯ���Ѵ�.
					for (int up = LeftDown.y; up < RightTop.y + 1; ++up)
					{
						// �������� ���� �ƴϸ� ����������.
						int test = RightTop.x + 1 + up * m_Col;
						if (m_vecTile[test].second != CREATURE_ID::Wall)
						{
							ROK = false;
							break;
						}
					}

					bool TOK = true;

					// ���� ���� �Ʒ��� ��� �����ϴ� �� Ȯ���Ѵ�.
					for (int right = LeftDown.x; right < RightTop.x + 1; ++right)
					{
						// ���� ���� �ƴϸ� ����������.
						int test = right  + (RightTop.y + 1) * m_Col;
						if (m_vecTile[test].second != CREATURE_ID::Wall)
						{
							TOK = false;
							break;
						}
					}


					if (TOK && ROK)
					{
						//������ ���� �� �� �ִ�.
						++RightTop.x;
						++RightTop.y;
					}
					else if (TOK)
					{
						++RightTop.y;
					}
					else if (ROK)
					{
						++RightTop.x;;
					}
					else
					{
						break;
					}
				
				}
				else
				{
					// ������ ���� �����Ѵٸ� 
					if (RightTop.x + 1 < m_Col && m_vecTile[r].second == CREATURE_ID::Wall && DArray[r] == 0)
					{
						// ������ �� ��� Ȯ��
						bool OK = true;
						// ������ ���� �Ʒ��� ��� �����ϴ� �� Ȯ���Ѵ�.
						for (int up = LeftDown.y; up < RightTop.y + 1; ++up)
						{
							// �������� ���� �ƴϸ� ����������.
							int test = RightTop.x + 1 + up * m_Col;
							if (m_vecTile[test].second != CREATURE_ID::Wall)
							{
								OK = false;
								break;
							}
						}

						// ��� ���̶�� 1 RightTop�� 1 ������Ų��.
						if (OK)
							++RightTop.x;
						else
							break;
					}
					// �� ���� ���� �Ѵٸ�
					else if (RightTop.y + 1 < m_Row && m_vecTile[t].second == CREATURE_ID::Wall && DArray[t] == 0)
					{
						// �� �� ��� Ȯ��
						bool OK = true;
						// ���� ���� �Ʒ��� ��� �����ϴ� �� Ȯ���Ѵ�.
						for (int right = LeftDown.x; right < RightTop.x + 1; ++right)
						{
							// ���� ���� �ƴϸ� ����������.
							int test = right + (RightTop.y + 1) * m_Col;
							if (m_vecTile[test].second != CREATURE_ID::Wall)
							{
								OK = false;
								break;
							}
						}

						// ��� ���̶�� 1 RightTop�� 1 ������Ų��.
						if (OK)
							++RightTop.y;
						else
							break;
					}
					else
						break;
				}
				
			}

			CObj* pWall = GPrefabManager::GetInst()->GetInst()->CreatePrefab(CREATURE_ID::Wall);
			CreateChildGameObject(GetOwner(), pWall, LAYER_TYPE::OBJECT);
			Vec2 Scale = (RightTop - LeftDown) + Vec2(1.f, 1.f);
			Vec2 Pos = LeftDown + Scale / 2;
			pWall->SetPos(Pos * 64.f);
			pWall->GetComponent<GBoxCollider>()->SetScale(Scale * 64);

			for (int col = LeftDown.x; col < RightTop.x + 1; ++col)
			{
				for (int row = LeftDown.y; row < RightTop.y + 1; ++row)
				{
					DArray[row * m_Col + col] = num;
				}
			}
			++num;
			

		}
	}

	DArray;
}



void GTileMap::CreatCreature_Pos(CREATURE_ID _CreatureID, int Row, int Col)
{
	if (IsValid(m_vecCreature[Row * m_Col + Col]))
	{
		DeleteGameObject(m_vecCreature[Row * m_Col + Col]);
		m_vecCreature[Row * m_Col + Col] = nullptr;
	}
	
	if (_CreatureID == CREATURE_ID::NONE || _CreatureID == CREATURE_ID::Wall)
		return;

	CObj* CreatureObj = GPrefabManager::GetInst()->CreatePrefab(_CreatureID);
	LAYER_TYPE LayerType = LAYER_TYPE::END;

	if ((int)CREATURE_ID::Monster < (int)_CreatureID && (int)_CreatureID < (int)CREATURE_ID::Obstacle)
		LayerType = LAYER_TYPE::MONSTER;
	else if ((int)CREATURE_ID::Obstacle < (int)_CreatureID && (int)_CreatureID < (int)CREATURE_ID::Item)
		LayerType = LAYER_TYPE::OBJECT;
	else if ((int)CREATURE_ID::Item < (int)_CreatureID && (int)_CreatureID < (int)CREATURE_ID::ELEMENT)
		LayerType = LAYER_TYPE::ITEM;
	else if ((int)CREATURE_ID::ELEMENT < (int)_CreatureID && (int)_CreatureID < (int)CREATURE_ID::ETC)
		LayerType = LAYER_TYPE::ELEMENT;
	else if ((int)CREATURE_ID::HitBox == (int)_CreatureID)
		LayerType = LAYER_TYPE::OBJECT;
	else if ((int)CREATURE_ID::Wall == (int)_CreatureID)
		LayerType = LAYER_TYPE::OBJECT;

	if (CreatureObj != nullptr)
	{
		Vec2 Pos;
		Pos.x += m_Scale.x * TILE_SIZE * Col + m_Scale.x * TILE_SIZE / 2;
		Pos.y += m_Scale.y * TILE_SIZE * Row + m_Scale.x * TILE_SIZE / 2;
		CreatureObj->SetPos(Pos);
		CreateChildGameObject(GetOwner(), CreatureObj, LayerType);
	}

	m_vecCreature[Row * m_Col + Col] = CreatureObj;
}

void GTileMap::CreateCreature()
{

	for (int Row = 0; Row < m_Row; ++Row)
	{
		for (int Col = 0; Col < m_Col; ++Col)
		{

			// �ݸ� ȸ���� �´� ��Ŀ� ���ؼ� �̰� ���° Ÿ���������� 1���� �ε����� ��ȯ
			// �ش� Ÿ�������� �����Ѵ�.
			CREATURE_ID CreatureID = m_vecTile[Row * m_Col + Col].second;

			// Ÿ���� ����ִٸ� �׸��� �ʴ´�.
			if (CreatureID == CREATURE_ID::NONE)
				continue;

			// �������� �ʴ� Ÿ���̶�� ���Ʈ
			// ���� �ð��� ���� ��Ƹ����Ƿ� ����ȭ �ʿ�
			//assert(GAssetManager::GetInst()->FindTile(Tile->GetKey()) != nullptr);
			CreatCreature_Pos(CreatureID, Row, Col);
		}
	}

	Optimize();
}

void GTileMap::FinalTick()
{
	return;
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

	// ����ȭ
	Vec2 vCamLook = GCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// ������ ���� ���� ���� ���ϱ�
	Vec2 RightTop = vCamLook + vResolution / 2 - OwnerPos;
	int MaxRow = (int)(RightTop.y / (TILE_SIZE * m_Scale.y)) + 2;
	int MaxCol = (int)(RightTop.x / (TILE_SIZE * m_Scale.x)) + 2;

	MaxRow = MaxRow <= m_Row ? MaxRow : m_Row;
	MaxCol = MaxCol <= m_Col ? MaxCol : m_Col;

	// ���� �Ʒ��� ���� ���� ���ϱ�
	Vec2 LeftBottom = vCamLook - vResolution / 2 - OwnerPos;
	int MinRow = (int)(LeftBottom.y / (TILE_SIZE * m_Scale.y)) - 1;
	int MinCol = (int)(LeftBottom.x / (TILE_SIZE * m_Scale.x)) - 1;

	MinRow = MinRow >= 0 ? MinRow : 0;
	MinCol = MinCol >= 0 ? MinCol : 0;
	

	for (int Row = MinRow; Row < MaxRow; ++Row)
	{
		for (int Col = MinCol; Col < MaxCol; ++Col)
		{
			// Ÿ�� ����ȭ
			
			// �ݸ� ȸ���� �´� ��Ŀ� ���ؼ� �̰� ���° Ÿ���������� 1���� �ε����� ��ȯ
			// �ش� Ÿ�������� �����Ѵ�.
			const GTile* Tile = m_vecTile[Row * m_Col + Col].first;

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

