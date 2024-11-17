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

	int m_Row;	// Ÿ�� �� ����
	int m_Col;	// Ÿ�� �� ����

	vector<pair<const GTile*,CREATURE_ID>> m_vecTile;			// Ÿ���� �ּҸ� ���� ����

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

