#pragma once
#include "GCreature.h"

#include "GSprite.h"


class GItem :
	public GCreature
{
	GSprite* m_ItemImage;
public:

	void SetItemImage(GSprite* _Image) { m_ItemImage = _Image; }
	GSprite* GetItemImage() { return m_ItemImage; }


public:
	virtual void UseItem(GCreature* _User) = 0;

public:
	GItem(CREATURE_ID _CreatureID);
	virtual ~GItem() override;
};

