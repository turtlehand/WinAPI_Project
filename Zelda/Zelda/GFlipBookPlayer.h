#pragma once
#include "Component.h"
class GFlipBook;

class GFlipBookPlayer : public Component
{
private:
	vector<GFlipBook*>	m_vecFlipBook;	// FlipBook 목록
	GFlipBook*			m_CurFlipBook;	// 현재 재생중인 FlipBook
	int					m_SpriteIdx;		

	float				m_FPS;			// FlipBook 재생속도
	float				m_Time;			// 누적시간
	bool				m_Repeat;		// 반복 재생 여부
	bool				m_Finish;		// 재생이 끝났는지 여부
public:
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

public:
	virtual void FinalTick() override;
	void Render();
public:
	GFlipBookPlayer();
	virtual ~GFlipBookPlayer() override;

};

