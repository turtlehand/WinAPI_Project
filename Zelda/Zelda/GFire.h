#pragma once
#include "GHitBox.h"
class GFire :
    public GHitBox
{
public:
    virtual void Awake() override;
    virtual void Begin() override;

public:
    GFire();
    virtual ~GFire() override;
};

