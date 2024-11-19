#pragma once
#include "GState.h"

class GMonster;

class GMChaseState : public GState
{
private:
	GMonster* m_Monster;
	MonsterInfo* m_MonsterInfo;
	Vec2 m_PrevDir;

public:
	virtual void Awake() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
public:
	GMChaseState();
	~GMChaseState();
};

