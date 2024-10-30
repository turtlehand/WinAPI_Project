#pragma once
#include "GComponent.h"
class GFlipBook;

class GTexture;

class GFlipBookPlayer : public GComponent
{
private:
	vector<GFlipBook*>	m_vecFlipBook;	// FlipBook 목록
	GFlipBook*			m_CurFlipBook;	// 현재 재생중인 FlipBook
	int					m_SpriteIdx;

	float				m_FPS;			// FlipBook 재생속도
	float				m_Time;			// 누적시간
	bool				m_Repeat;		// 반복 재생 여부
	bool				m_Finish;		// 재생이 끝났는지 여부

	Vec2				m_Scale;
	int					m_Alpha;
	COLORREF			m_DeleteColor;

	bool				m_XFlip;
	bool				m_YFlip;

	GTexture*			m_RenderTexture;// Render 시킬 Texture
public:
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	void SetAlpha(int _Alpha) { m_Alpha = _Alpha; }

	void SetDeleteColor(COLORREF _DeleteColor) { m_DeleteColor = _DeleteColor; }

	void SetXFlip(bool _XFlip) { m_XFlip = _XFlip; }

	void SetYFlip(bool _YFlip) { m_YFlip = _YFlip; }

	void AddFlipBook(GFlipBook* _FlipBook) { m_vecFlipBook.push_back(_FlipBook); }
	void AddFlipBook(int _idx, GFlipBook* _FlipBook)
	{
		if (m_vecFlipBook.size() <= _idx)
		{
			m_vecFlipBook.resize(_idx + 1);

		}
		m_vecFlipBook[_idx] = _FlipBook;
	}

	void Play(int _FlipBookIdx, float _FPS, bool _Repeat)
	{
		m_CurFlipBook = m_vecFlipBook[_FlipBookIdx];
		m_SpriteIdx = 0;
		m_FPS = _FPS;
		m_Repeat = _Repeat;
		m_Finish = false;
		m_Time = 0.f;
	}

	bool IsFinish() { return m_Finish; }

	void Reset()
	{
		m_Finish = false;
		m_SpriteIdx = 0;
	}

private:
	void XFlip(GTexture*& _Textrue);
	void YFlip(GTexture*& _Textrue);
	void DeleteColor(GTexture*& _Textrue);
	void Alpha(GTexture*& _Texture);
	void DeleteColorAlpha(GTexture*& _Textrue);

public:
	virtual void FinalTick() override;
	void Render();
public:
	GFlipBookPlayer();
	virtual ~GFlipBookPlayer() override;

};

