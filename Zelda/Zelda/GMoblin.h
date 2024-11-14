#pragma once
#include "GMonster.h"

class GMoblin :
    public GMonster
{
public:
    virtual void Awake() override;
    virtual void Tick() override;
    virtual void Render() override;

protected:
    virtual void CreateAnimator() override;

public:
    GMoblin();
    virtual ~GMoblin();
};

