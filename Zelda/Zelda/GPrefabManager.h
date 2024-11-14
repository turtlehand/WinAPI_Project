#pragma once
#include "GCreature.h"

class GCreature;

class GPrefabManager
{
private:
	SINGLE(GPrefabManager);

private:
	map<CREATURE_ID, CObj*> m_mapPrefab;
public:
	void Init();
	const CObj* FindPrefab(CREATURE_ID _Key);
	CObj* CreatePrefab(CREATURE_ID _Key);
};

