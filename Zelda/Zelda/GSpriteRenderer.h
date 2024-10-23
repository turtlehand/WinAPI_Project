#pragma once
#include "GComponent.h"

class GSprite;

class GSpriteRenderer :
    public GComponent
{
private:
    GSprite* m_Sprite;
    Vec2 m_Scale;
    int m_Alpha;
    COLORREF m_DeleteColor;

    bool m_XFlip;
    bool m_YFlip;
    
public:
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetSprite(GSprite* _Sprite) { m_Sprite = m_Sprite; }
    const GSprite* GetSprite() { return m_Sprite; }

    void SetAlph(int _Alpha) { m_Alpha = m_Alpha; }
    
    void SetDeleteColor(COLORREF _DeleteColor) { m_DeleteColor = _DeleteColor; }

    void SetXFlip(bool _XFlip) { m_XFlip = _XFlip; }

    void SetYFlip(bool _YFlip) { m_YFlip = _YFlip; }

public:
    virtual void FinalTick() override;
    virtual void Render();
public:
    GSpriteRenderer();
    virtual ~GSpriteRenderer() override;

};

