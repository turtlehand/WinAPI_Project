#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GRoastFruit :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void Begin() override;
	//void Tick() override;
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;


	virtual void UseItem(GCreature* _User) override;
	virtual void DropItem() override;

public:
	GRoastFruit();
	virtual ~GRoastFruit() override;
};