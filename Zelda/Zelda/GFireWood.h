#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GFireWood :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void UseItem(GCreature* _User) override {};

public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void Render() override;


public:
	GFireWood();
	virtual ~GFireWood() override;
};

