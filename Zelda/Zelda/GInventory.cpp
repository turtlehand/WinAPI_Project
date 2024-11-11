#include "pch.h"
#include "GInventory.h"

#include "GCreature.h"
#include "GFireWood.h"
#include "GFlint.h"
#include "GFruit.h"
#include "GRoastFruit.h"
#include "GWeapon.h"

#include "GTexture.h"
#include "GSprite.h"

GInventory::GInventory() :
	m_Item{},
	m_CurImage(nullptr)
{
	m_Item.insert(make_pair(ITEM_ID::Fire_Wood, new GFireWood));
	m_Item.insert(make_pair(ITEM_ID::Flint, new GFlint));
	m_Item.insert(make_pair(ITEM_ID::Fruit, new GFruit));
	m_Item.insert(make_pair(ITEM_ID::Roast_Fruit, new GRoastFruit));
	m_Item.insert(make_pair(ITEM_ID::Wooden_Sword, new GWeapon(ITEM_ID::Wooden_Sword)));
	m_Item.insert(make_pair(ITEM_ID::Iron_Sword, new GWeapon(ITEM_ID::Iron_Sword)));
}

GInventory::~GInventory()
{
	Delete_Map(m_Item);
}

void GInventory::UseItem(ITEM_ID _ItemID, GCreature* _User)
{
	map<ITEM_ID, GItem*>::iterator iter = m_Item.find(_ItemID);
	assert(iter != m_Item.end());

	iter->second->UseItem(_User);
}

const GItem* GInventory::FindItem(ITEM_ID _ItemID)
{
	map<ITEM_ID, GItem*>::iterator iter = m_Item.find(_ItemID);
	assert(iter != m_Item.end());

	return iter->second;
}

void GInventory::SetCurItme(ITEM_ID _ItemID)
{

	if (_ItemID == ITEM_ID::NONE)
	{
		m_CurImage = nullptr;
		return;
	}
		

	map<ITEM_ID, GItem*>::iterator iter = m_Item.find(_ItemID);
	assert(iter != m_Item.end());
	m_CurImage = iter->second->GetItemImage();
}

void GInventory::Tick_UI()
{

}

void GInventory::Render_UI()
{
	if (m_CurImage == nullptr)
		return;

	StretchBlt(CEngine::GetInst()->GetSecondDC(),
		CEngine::GetInst()->GetResolution().x - 100, 50,
		64, 64,
		m_CurImage->GetAtlas()->GetDC(), m_CurImage->GetLeftTop().x, m_CurImage->GetLeftTop().y,
		m_CurImage->GetSlice().x, m_CurImage->GetSlice().y, SRCCOPY);
}