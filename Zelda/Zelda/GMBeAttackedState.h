#pragma once
#include "GState.h"

class GMonster;

class GMBeAttackedState :
    public GState
{
private:
    GMonster* m_Monster;
    float m_Timer;

public:
    virtual void Begin() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GMBeAttackedState();
    ~GMBeAttackedState();
};