#pragma once
#include "CLevel.h"
#include "GMap.h"
#include "GTilePalette.h"

enum class DRAW_MODE_TYPE
{
	TILE,
	OBJECT,
	NONE,
};

class GLevel_Editor :
    public CLevel
{
private:
	DRAW_MODE_TYPE m_DrawMode;

	GMap* m_MapObj;
	GTilePalette* m_TilePalette;
	int m_CurIndex;

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
	void SaveTilePalette();
	void LoadTilePalette();

	void SaveTileMap();
	void LoadTileMap();

public:
	GMap* GetMapObject() { return m_MapObj; }
	GTilePalette* GetTilePalette() { return m_TilePalette; }
};

