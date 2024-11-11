#pragma once
#include "GUI.h"
#include "GItem.h"

class GInventory :
	public GUI
{
private:
	map<ITEM_ID, GItem*> m_Item;
	GSprite* m_CurImage;

public:
	void UseItem(ITEM_ID _ItemID, GCreature* _User);
	const GItem* FindItem(ITEM_ID _ItemID);

	void SetCurItme(ITEM_ID _ItemID);

public:
	virtual void Tick_UI() override;
	virtual void Render_UI() override;

public:
	GInventory();
	virtual ~GInventory() override;
};

