#pragma once
#include "Component.h"
class GTexture;

class GTileMap : public Component
{
private:
	int m_Row;	// Ÿ�� �� ����
	int m_Col;	// Ÿ�� �� ����
	
	GTexture* m_Atlas;			
	int m_AtlasTileRow;			// ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
	int m_AtlasTileCol;			// ��Ʋ�� �ؽ��� �ȿ� �ִ� Ÿ�� �� ����
	Vec2 m_AtlasResolution;		// ��Ʋ�� �ػ�

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

