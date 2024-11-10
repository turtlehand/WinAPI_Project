#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GFireWood :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void BurnStatusEffect();

public:
	virtual void Begin() override;
	//void Tick() override;
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	virtual void UseItem() override {};

public:
	GFireWood();
	virtual ~GFireWood() override;
};

