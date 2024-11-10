#pragma once
#include "GCreature.h"

enum class ITEM_ID
{
	NONE = 0,
	MATERIALS = 100,
	Fire_Wood,
	Flint,
	MonsterMaterial,


	FOOD = 200,
	Fruit,
	Roast_Fruit,


	WEAPON = 300,
	Wooden_Sword,
	Iron_Sword,
	Stone_Hammer,
	Iron_Hammer,
	Wooden_Spear,
	Spear,
	Korok_Leaf,


	TOOLS = 400,
	Bow,
	Arrow,
};


class GItem :
	public GCreature
{
	const ITEM_ID m_ItemID;
public:
	ITEM_ID GetItemID() { return m_ItemID; }

public:
	virtual void UseItem() = 0;

public:
	GItem(ITEM_ID _ItemID);
	virtual ~GItem() override;
};

