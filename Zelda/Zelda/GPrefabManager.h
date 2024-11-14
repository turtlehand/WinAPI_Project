#pragma once
#include "GCreature.h"

class CObj;

class GPrefabManager
{
private:
	SINGLE(GPrefabManager);

private:
	map<UINT, CObj*> m_mapPrefab;
public:
	void Init();
	const CObj* FindPrefab(CREATURE_ID _Key);
	CObj* CreatePrefab(CREATURE_ID _Key);

};

