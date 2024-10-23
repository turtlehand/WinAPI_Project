#pragma once
#include "Component.h"
class GTexture;

class GTileMap : public Component
{
private:
	int m_Row;	// 타일 행 개수
	int m_Col;	// 타일 열 개수
	
	GTexture* m_Atlas;			
	int m_AtlasTileRow;			// 아틀라스 텍스펴 안에 있는 타일 열 개수
	int m_AtlasTileCol;			// 아틀라스 텍스쳐 안에 있는 타일 행 개수
	Vec2 m_AtlasResolution;		// 아틀라스 해상도

	vector<Tile> m_vecTile;

public:
	void SetRowCol(int _Row, int _Col);
	void SetAtlasTexture(GTexture* _Atlas);

	Tile* GetTile(Vec2 _MousePos);

	bool Save(wstring _FullPath);
	bool Load(wstring _FullPath);

public:
	virtual void FinalTick() override;
	void Render();

public:
	 GTileMap();
	 virtual~GTileMap() override;
};

