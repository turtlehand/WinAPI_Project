#include "pch.h"
#include "GTileMap.h"

#include "GComponent.h"
#include "GTexture.h"

#include "GCamera.h"
#include "GPathManager.h"

GTileMap::GTileMap() :
	GComponent(COMPONENT_TYPE::TILEMAP),
	m_Row(0),
	m_Col(0),
	m_Atlas(nullptr),
	m_AtlasTileRow(0),
	m_AtlasTileCol(0),
	m_AtlasResolution()
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
		m_vecTile[i].ImgIdx = -1;
	}
}

void GTileMap::SetAtlasTexture(GTexture* _Atlas)
{
	m_Atlas = _Atlas;

	if (nullptr == m_Atlas)
		return;
	m_AtlasResolution = Vec2((float)m_Atlas->GetWidth(), (float)m_Atlas->GetHeight());
	m_AtlasTileRow = m_AtlasResolution.y / TILE_SIZE;
	m_AtlasTileCol = m_AtlasResolution.x / TILE_SIZE;
}

Tile* GTileMap::GetTile(Vec2 _MousePos)
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

bool GTileMap::Save(wstring _FullPath)
{
	FILE* File = nullptr;

	_wfopen_s(&File, _FullPath.c_str(), L"wb");
	assert(File);

	fwrite(&m_Row, sizeof(int), 1, File);
	fwrite(&m_Col, sizeof(int), 1, File);

	SaveAssetRef(m_Atlas, File);

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		fwrite(&m_vecTile[i], sizeof(Tile), 1, File);
	}

	fclose(File);

	return true;
}

bool GTileMap::Load(wstring _FullPath)
{
	FILE* File = nullptr;

	_wfopen_s(&File, _FullPath.c_str(), L"rb");
	assert(File);

	fread(&m_Row, sizeof(int), 1, File);
	fread(&m_Col, sizeof(int), 1, File);
	SetRowCol(m_Row, m_Col);

	m_Atlas = (GTexture*)LoadAssetRef(File);
	SetAtlasTexture(m_Atlas);

	for (size_t i = 0; i < m_Row * m_Col; ++i)
	{
		fread(&m_vecTile[i], sizeof(Tile), 1, File);
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
			OwnerPos + Vec2(0, i * TILE_SIZE),
			OwnerPos + Vec2(m_Col * TILE_SIZE, i * TILE_SIZE));
	}

	for (int i = 0; i < m_Col + 1; ++i)
	{
		DrawDebugLine(PEN_TYPE::GREEN, 0.f, 
			OwnerPos + Vec2(i * TILE_SIZE, 0),
			OwnerPos + Vec2(i * TILE_SIZE, m_Row * TILE_SIZE));
	}
}

void GTileMap::Render()
{
	if (nullptr == m_Atlas)
		return;

	Vec2 OwnerPos = GetOwner()->GetPos();
	Vec2 OwnerRenderPos = GetOwner()->GetRenderPos();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	int ImgIdx = 0;
	int ImgRow = ImgIdx / m_AtlasTileCol;
	int ImgCol = ImgIdx % m_AtlasTileCol;

	// 최적화
	Vec2 vCamLook = GCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	// 오른쪽 위의 열과 행을 구하기
	Vec2 RightTop = vCamLook + vResolution / 2 - OwnerPos;
	int MaxRow = (int)(RightTop.y / TILE_SIZE) + 1;
	int MaxCol = (int)(RightTop.x / TILE_SIZE) + 1;

	MaxRow = MaxRow <= m_Row ? MaxRow : m_Row;
	MaxCol = MaxCol <= m_Col ? MaxCol : m_Col;

	// 왼쪽 아래의 열과 행을 구하기
	Vec2 LeftBottom = vCamLook - vResolution / 2 - OwnerPos;
	int MinRow = (int)(LeftBottom.y / TILE_SIZE);
	int MinCol = (int)(LeftBottom.x / TILE_SIZE);

	MinRow = MinRow >= 0 ? MinRow : 0;
	MinCol = MinCol >= 0 ? MinCol : 0;
	

	for (int Row = MinRow; Row < MaxRow; ++Row)
	{
		for (int Col = MinCol; Col < MaxCol; ++Col)
		{

			// 반목문 회차에 맞는 행렬에 대해서 이게 몇번째 타일정보인지 1차원 인덱스로 변환
			// 해당 타일정보에 접근한다.
			ImgIdx = m_vecTile[Row * m_Col + Col].ImgIdx;
			ImgRow = ImgIdx / m_AtlasTileCol;
			ImgCol = ImgIdx % m_AtlasTileCol;

			// -1일 시 비어있다는 의미
			if (ImgIdx == -1)
				continue;

			assert(0 <= ImgIdx && ImgIdx < m_AtlasTileCol * m_AtlasTileRow);

			BitBlt(dc,
				(int)OwnerRenderPos.x + Col * TILE_SIZE, (int)OwnerRenderPos.y - Row * TILE_SIZE - TILE_SIZE,
				TILE_SIZE, TILE_SIZE,
				m_Atlas->GetDC(), ImgCol * TILE_SIZE, ImgRow * TILE_SIZE, SRCCOPY);
		}
	}
}

