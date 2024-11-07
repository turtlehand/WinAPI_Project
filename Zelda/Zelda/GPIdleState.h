#pragma once
#include "GState.h"

class GPlayer;

class GPIdleState : public GState
{
private:
    GPlayer* m_Player;

public:
    virtual void Begin() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GPIdleState();
    ~GPIdleState();
};

