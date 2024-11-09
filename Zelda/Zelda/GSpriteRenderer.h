#pragma once
#include "GComponent.h"

class GSprite;
class GTexture;

class GSpriteRenderer :
	public GComponent
{
private:
	GSprite*			m_Sprite;

	RenderInfo			m_RenderInfo;

	GTexture*           m_RenderTexture;        // Render Ω√≈≥ Texture
	
public:
	void SetSprite(GSprite* _Sprite) { m_Sprite = _Sprite; }
	const GSprite* GetSprite() { return m_Sprite; }

	void SetOffset(Vec2 _Offset) { m_RenderInfo.Offset = _Offset; }

	void SetScale(Vec2 _Scale) { m_RenderInfo.Scale = _Scale; }

	void SetAlpha(int _Alpha) { m_RenderInfo.Alpha = _Alpha; }

	void SetDeleteColor(COLORREF _DeleteColor) { m_RenderInfo.DeleteColor = _DeleteColor; }

	void SetXFlip(bool _XFlip) { m_RenderInfo.XFlip = _XFlip; }

	void SetYFlip(bool _YFlip) { m_RenderInfo.YFlip = _YFlip; }

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

