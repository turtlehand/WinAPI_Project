#pragma once
#include "GState.h"

class GMonster;

class GMChaseState : public GState
{
private:
	GMonster* m_Monster;

public:
	virtual void Begin() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
public:
	GMChaseState();
	~GMChaseState();
};

