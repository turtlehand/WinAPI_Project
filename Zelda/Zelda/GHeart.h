#pragma once
#include "GPanel.h"

class GSprite;

class GHeart :
    public GPanel
{
private:
    GSprite* m_HeartSprite[3];
	const DefaultStatsInfo& m_PlayerInfo;

public:
	virtual void Awake() override;
	virtual void Tick_UI() override;
	virtual void Render_UI() override;

public:
	GHeart(const DefaultStatsInfo& _PlayerInfo);
	virtual ~GHeart() override;
};

