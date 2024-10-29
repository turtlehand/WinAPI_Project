#pragma once
#include "GComponent.h"
class GTilePalette;
class GTile;

class GTileMap : public GComponent
{
private:
	Vec2 m_Scale;

	int m_Row;	// 타일 행 개수
	int m_Col;	// 타일 열 개수

	vector<const GTile*> m_vecTile;			// 타일의 주소를 갖는 벡터

public:
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	Vec2 GetScale() { return m_Scale; }

	void SetRowCol(int _Row, int _Col);

	void SetTile(Vec2 _MousePos, GTile* _Tile = nullptr);

	//const GTile** GetTile(Vec2 _MousePos);

	int Save(const wstring& _FullPath);
	int Load(const wstring& _FullPath);

public:
	virtual void FinalTick() override;
	void Render();

public:
	 GTileMap();
	 virtual~GTileMap() override;
};

