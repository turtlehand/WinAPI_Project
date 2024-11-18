#pragma once
#include "GPanel.h"

#define RED 0
#define BLUE 1

class GSlot :
    public GPanel
{
private:
    GSprite* m_ItemSprite;
    GSprite* m_BackGroundSprite[2];
    bool m_Color;

public:
    GSprite* GetItemSprite() { return m_ItemSprite; }
    void SetItemSprite(GSprite* _ItemSprite) { m_ItemSprite = _ItemSprite; }
    void ChangeColor(){ m_Color = !m_Color; }

public:
    virtual void Awake() override;
    virtual void Tick_UI() override;
    virtual void Render_UI() override;
public:
    GSlot();
    ~GSlot() ;

};

