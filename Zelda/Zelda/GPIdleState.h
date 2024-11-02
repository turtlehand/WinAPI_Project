#pragma once
#include "GState.h"

class Player;

class GPIdleState : public GState
{
private:
    Player* m_Player;

public:
    virtual void Awake() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GPIdleState();
    ~GPIdleState();
};
