#pragma once
#include "CLevel.h"
class GPlayer;
class GMap;

class GLevel_Stage_1 :
	public CLevel
{
private:
	GPlayer* m_Player;
	GMap* m_Map;

public:
	GLevel_Stage_1();
	virtual ~GLevel_Stage_1() override;

public:
	virtual void Begin() override;
	virtual void End() override;
	virtual void Tick() override;
	virtual void Render() override;
};


