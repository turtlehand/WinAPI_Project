#include "pch.h"
#include "GMap.h"

#include "GTileMap.h"
#include "GAssetManager.h"

GMap::GMap() :
	m_TileMap(nullptr)
{
	m_TileMap = AddComponent<GTileMap>();
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


