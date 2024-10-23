#include "pch.h"
#include "GMap.h"

#include "GTileMap.h"
#include "GAssetManager.h"

GMap::GMap() :
	m_TileMap(nullptr)
{
	m_TileMap = AddComponent<GTileMap>();
	m_TileMap->SetRowCol(0, 0);
	m_TileMap->SetAtlasTexture(GAssetManager::GetInst()->LoadTexture(L"Tile", L"Texture\\TILE.bmp"));
}

GMap::~GMap()
{
}

void GMap::Begin()
{
}

void GMap::Tick()
{
	
}

void GMap::Render()
{
	m_TileMap->Render();
}


