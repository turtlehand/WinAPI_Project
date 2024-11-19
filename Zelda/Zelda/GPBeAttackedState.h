#pragma once
#include "GState.h"

class GPlayer;
class GSound;

class GPBeAttackedState :
	public GState
{
private:
	GPlayer* m_Player;
	float m_Timer;

	GSound* m_HurtSound;

public:
	virtual void Awake() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;
public:
	GPBeAttackedState();
	~GPBeAttackedState();
};