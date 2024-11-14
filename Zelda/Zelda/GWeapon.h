#pragma once
#include "GItem.h"
#include "GSpriteRenderer.h"

class GSpriteRenderer;

class GWeapon :
	public GItem
{
private:
	GSpriteRenderer* m_SpriteRenderer;
	GSprite* m_SpriteX;
	GSprite* m_SpriteY;

public:
	virtual void Begin() override;
	virtual void Render() override;

public:
	virtual void UseItem(GCreature* _User) override;

public:
	const WeaponInfo* GetWeaponInfo() { return (WeaponInfo*)GetStatInfo(); }
	const GSprite* GetSprite() { return m_SpriteRenderer->GetSprite(); };

public:
	void SpecialEffect();

public:
	GWeapon(CREATURE_ID _CreatureID);
	virtual ~GWeapon() override;
};

