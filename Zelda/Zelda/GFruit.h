#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GFruit :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void Awake() override;
	//void Tick() override;
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;


	virtual void UseItem(GCreature* _User) override;
	virtual void DropItem() override;

public:
	GFruit();
	virtual ~GFruit() override;
};
