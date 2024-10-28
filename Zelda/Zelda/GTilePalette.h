#pragma once
#include "GAsset.h"

class GTile;

class GTilePalette :
    public GAsset
{
private:
    vector<GTile*> m_Tile;

public:
    GTile* const GetTile(Vec2 _MousePos);
	GTile* const GetTile(int _Index) { return m_Tile[_Index]; }

	int const GetTileSize() { return m_Tile.size(); }

public:
	virtual int Save(const wstring& _RelativePath) override;
	virtual int Load(const wstring& _RelativePath) override;
	//void Create(GSprite* _Sprite, bool _Collider);

public:
	GTilePalette();
	virtual ~GTilePalette() override;

};

