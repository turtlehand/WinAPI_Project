#pragma once
#include "GState.h"

class GMonster;
class GSound;

class GMDieState :
    public GState
{
private:
    GMonster* m_Monster;

public:
    virtual void Awake() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;
public:
    GMDieState();
    ~GMDieState();
};

