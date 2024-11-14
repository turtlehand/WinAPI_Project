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
	virtual void Awake() override;			// ������ ���۵� ��
	virtual void Tick() override;			// ������Ʈ�� �� ��
	virtual void Render() override;			// ������Ʈ�� �׸���

public:
	GMap();
	virtual ~GMap() override;
};

