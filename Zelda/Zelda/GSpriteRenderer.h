#pragma once
#include "GComponent.h"

class GSprite;
class GTexture;

class GSpriteRenderer :
    public GComponent
{
private:
    GSprite* m_Sprite;

    Vec2				m_Scale;
    int					m_Alpha;
    COLORREF			m_DeleteColor;

    bool				m_XFlip;
    bool				m_YFlip;

    GTexture*           m_RenderTexture;        // Render Ω√≈≥ Texture
    
public:
    void SetSprite(GSprite* _Sprite) { m_Sprite = _Sprite; }
    const GSprite* GetSprite() { return m_Sprite; }

    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetAlpha(int _Alpha) { m_Alpha = _Alpha; }

    void SetDeleteColor(COLORREF _DeleteColor) { m_DeleteColor = _DeleteColor; }

    void SetXFlip(bool _XFlip) { m_XFlip = _XFlip; }

    void SetYFlip(bool _YFlip) { m_YFlip = _YFlip; }

private:
    void XFlip(GTexture*& _Texture);
    void YFlip(GTexture*& _Texture);
    void DeleteColor(GTexture*& _Texture);
    void Alpha(GTexture*& _Texture);
    void DeleteColorAlpha(GTexture*& _Texture);

public:
    virtual void FinalTick() override;
    virtual void Render();
public:
    GSpriteRenderer();
    virtual ~GSpriteRenderer() override;

};

