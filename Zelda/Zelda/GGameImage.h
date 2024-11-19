#pragma once
#include "GPanel.h"

class GGameImage :
    public GPanel
{
private:
    GSprite* m_Sprite;

public:
    GSprite* GetSprite() { return m_Sprite; }
    void SetSprite(GSprite* _Sprite) { m_Sprite = _Sprite; }

public:
    virtual void Awake() override;
    virtual void Tick_UI() override;
    virtual void Render_UI() override;
public:
    GGameImage();
    ~GGameImage();

};