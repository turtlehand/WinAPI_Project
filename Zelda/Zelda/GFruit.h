#pragma once
#include "GItem.h"

class GSpriteRenderer;

class GFruit :
	public GItem
{
	GSpriteRenderer* m_SpriteRenderer;

public:
	virtual void Begin() override;
	//void Tick() override;
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	virtual void UseItem() override;
	virtual void DropItem() override;

public:
	GFruit();
	virtual ~GFruit() override;
};
