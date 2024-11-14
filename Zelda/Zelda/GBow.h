#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GBow :
	public GItem
{
private:
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void Awake() override;
	virtual void Render() override;

public:
	virtual void UseItem(GCreature* _User) override;

public:
	GBow();
	virtual ~GBow() override;
};

