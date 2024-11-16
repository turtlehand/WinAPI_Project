#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GFlint :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void InteractionEffect_Attack(GHitBox* _HitBox) override;
	virtual void UseItem(GCreature* _User) override {};

public:
	virtual void Awake() override;
	virtual void Render() override;


public:
	GFlint();
	virtual ~GFlint() override;
};

