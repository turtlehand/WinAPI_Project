#include "pch.h"
#include "GItem.h"

GItem::GItem(CREATURE_ID _CreatureID) :
	GCreature(_CreatureID),
	m_ItemImage(nullptr)
{
}

GItem::~GItem()
{
}
