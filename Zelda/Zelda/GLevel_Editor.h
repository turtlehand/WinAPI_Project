#pragma once
#include "CLevel.h"
#include "GMap.h"
#include "GTilePalette.h"

class GLevel_Editor :
    public CLevel
{
private:
	GMap* m_MapObj;
	GTilePalette* m_TilePalette;
	GTile* m_CurTile;

	HMENU m_hMenu;

public:
	GLevel_Editor();
	virtual ~GLevel_Editor() override;

public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void Render() override;
	virtual void End() override;
	
public:
	void LoadTilePalette();
	//void SaveTileMap();
	//void LoadTileMap();

public:
	GMap* GetMapObject() { return m_MapObj; }
	GTilePalette* GetTilePalette() { return m_TilePalette; }
};

