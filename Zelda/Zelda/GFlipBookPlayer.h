#pragma once
#include "GComponent.h"
class GFlipBook;

class GTexture;

class GFlipBookPlayer : public GComponent
{
private:
	vector<GFlipBook*>	m_vecFlipBook;			// FlipBook ���
	int					m_CurFlipBookIndex;		// ���� ������� FlipBook
	int					m_SpriteIdx;

	float				m_FPS;					// FlipBook ����ӵ�
	float				m_Time;					// �����ð�
	bool				m_Repeat;				// �ݺ� ��� ����
	bool				m_Play;					// ��� ����
	bool				m_Finish;				// ����� �������� ����

	bool				m_XFlip;
	bool				m_YFlip;

	GTexture*			m_RenderTexture;		// Render ��ų Texture
public:

	void SetXFlip(bool _XFlip) { m_XFlip = _XFlip; }

	void SetYFlip(bool _YFlip) { m_YFlip = _YFlip; }

	// ��� ����
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

