#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GFlint :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void InteractionEffect(GHitBox* _HitBox) override;

public:
	virtual void Begin() override;
	//void Tick() override;
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	virtual void UseItem() override {};

public:
	GFlint();
	virtual ~GFlint() override;
};

