#pragma once
#include "GAsset.h"

class GTile;

class GTilePalette :
    public GAsset
{
private:
    vector<GTile*> m_vecTile;

public:
	int AddTile(const wstring& Key, const wstring& _FullPath);

    GTile* const GetTile(Vec2 _MousePos);
	GTile* const GetTile(int _Index) { return m_vecTile[_Index]; }

	int const GetTileSize() { return m_vecTile.size(); }

public:
	virtual int Save(const wstring& _FullPath) override;
	virtual int Load(const wstring& _FullPath) override;
	//void Create(GSprite* _Sprite, bool _Collider);

public:
	GTilePalette();
	virtual ~GTilePalette() override;

};

