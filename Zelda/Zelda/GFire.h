#pragma once
#include "GHitBox.h"
class GFire :
    public GHitBox
{
public:
    virtual void Awake() override;

public:
    GFire();
    virtual ~GFire() override;
};

