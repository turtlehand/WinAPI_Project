#pragma once
#include "CLevel.h"

class GPlayer;
class GMap;

class GLevel_Start :
    public CLevel
{
private:
	GPlayer* m_Player;
	GMap* m_Map;

public:
	GLevel_Start();
	virtual ~GLevel_Start() override;

public:
	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick() override;
	virtual void Render() override;
};

