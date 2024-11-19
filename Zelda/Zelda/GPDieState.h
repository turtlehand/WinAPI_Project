#pragma once
#include "GState.h"


class GPlayer;

class GPDieState :
    public GState
{
private:
    GPlayer* m_Player;

public:
    virtual void Awake() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GPDieState();
    ~GPDieState();
};