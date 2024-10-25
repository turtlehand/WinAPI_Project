#pragma once
#include "GCollider.h"
class GCircleCollider :
    public GCollider
{
private:
    float m_Radius;

public:
    void SetRadius(float _Radius) { m_Radius = _Radius; }
    float GetRadius() { return m_Radius; };

public:
    virtual void FinalTick();

public:
    GCircleCollider();
    ~GCircleCollider();
};

