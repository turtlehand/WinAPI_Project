#pragma once
#include "GComponent.h"
class GFlipBook;

class GTexture;

class GFlipBookPlayer : public GComponent
{
private:
	vector<GFlipBook*>	m_vecFlipBook;			// FlipBook 목록
	int					m_CurFlipBookIndex;		// 현재 재생중인 FlipBook
	int					m_SpriteIdx;

	float				m_FPS;					// FlipBook 재생속도
	float				m_Time;					// 누적시간
	bool				m_Repeat;				// 반복 재생 여부
	bool				m_Play;					// 재생 여부
	bool				m_Finish;				// 재생이 끝났는지 여부

	bool				m_XFlip;
	bool				m_YFlip;
	float				m_Alpha;

	GTexture*			m_RenderTexture;		// Render 시킬 Texture
public:

	void SetXFlip(bool _XFlip) { m_XFlip = _XFlip; }

	void SetYFlip(bool _YFlip) { m_YFlip = _YFlip; }
	void SetAlpha(int _Alpha) { m_Alpha = (float)_Alpha; }

	// 재생 여부
	void Pause() { m_Play = false; }
	void Play() { m_Play = true; }

	void AddFlipBook(GFlipBook* _FlipBook) { m_vecFlipBook.push_back(_FlipBook); }
	void AddFlipBook(int _idx, GFlipBook* _FlipBook)
	{
		if (m_vecFlipBook.size() <= _idx)
		{
			m_vecFlipBook.resize(_idx + 1);

		}
		m_vecFlipBook[_idx] = _FlipBook;
	}

	void SetPlay(int _FlipBookIdx, float _FPS, bool _Repeat)
	{
		m_CurFlipBookIndex = _FlipBookIdx;
		m_SpriteIdx = 0;
		m_FPS = _FPS;
		m_Repeat = _Repeat;
		m_Finish = false;
		m_Time = 0.f;
		m_Play = true;
	}

	bool IsFinish() { return m_Finish; }

	void Reset()
	{
		m_Finish = false;
		m_SpriteIdx = 0;
	}

	int GetCurIndex() { return m_CurFlipBookIndex; }

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

