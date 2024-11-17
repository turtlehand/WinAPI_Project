#pragma once
#include "GComponent.h"
#include "GCreature.h"

class GSprite;
class GTilePalette;
class GTile;

class GTileMap : public GComponent
{
private:
	Vec2 m_Scale;

	int m_Row;	// 타일 행 개수
	int m_Col;	// 타일 열 개수

	vector<pair<const GTile*,CREATURE_ID>> m_vecTile;			// 타일의 주소를 갖는 벡터

public:
	void SetScale(Vec2 _Scale);
	Vec2 GetScale() { return m_Scale; }

	void SetRowCol(int _Row, int _Col);
	int GetRow() { return m_Row; }
	int GetCol() { return m_Col; }

	void SetTile(Vec2 _MousePos, GTile* _Tile = nullptr);
	void SetCreature(Vec2 _MousePos, CREATURE_ID _CreatureID = CREATURE_ID::NONE);

	//const GTile** GetTile(Vec2 _MousePos);
	CREATURE_ID GetCreatureID(int index) {
		assert(0 <= index && index < m_Row * m_Col);
		return m_vecTile[index].second;
	}

	int Save(const wstring& _FullPath);
	int Load(const wstring& _FullPath);

	

	void CreateCreature();
private:
	void Optimize();

public:
	virtual void FinalTick() override;
	void Render();

public:
	 GTileMap();
	 virtual~GTileMap() override;
};

