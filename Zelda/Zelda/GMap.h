#pragma once
#include "CObj.h"

class GTileMap;

class GMap :
    public CObj
{
private:
    GTileMap* m_TileMap;

public:
	GTileMap* GetTileMap() { return m_TileMap; }

public:
	virtual void Awake() override;			// 레벨이 시작될 때
	virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

public:
	GMap();
	virtual ~GMap() override;
};

