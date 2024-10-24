#pragma once
#include "GCollider.h"
class GBoxCollider :
    public GCollider
{
public:
    virtual void FinalTick();

public:
    GBoxCollider();
    ~GBoxCollider();
};

