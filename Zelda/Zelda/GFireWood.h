#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GFireWood :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void BurnStatusEffect();
	virtual void UseItem(GCreature* _User) override {};

public:
	virtual void Begin() override;
	//void Tick() override;
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	GFireWood();
	virtual ~GFireWood() override;
};

