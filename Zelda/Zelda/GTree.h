#pragma once
#include "GCreature.h"

class GSpriteRenderer;

class GTree :
    public GCreature
{
	GSpriteRenderer* m_Sprite;

public:
	virtual void DropItem();

public:
	virtual void Awake() override;			// 레벨이 시작될 때
	//virtual void Tick() override;			// 오브젝트가 할 일
	virtual void Render() override;			// 오브젝트를 그리기

public:
	GTree();
	virtual ~GTree() override;
};

