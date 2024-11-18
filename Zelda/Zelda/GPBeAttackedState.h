#pragma once
#include "GState.h"

class GPlayer;

class GPBeAttackedState :
    public GState
{
private:
    GPlayer* m_Player;
    float m_Timer;

public:
    virtual void Begin() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GPBeAttackedState();
    ~GPBeAttackedState();
};