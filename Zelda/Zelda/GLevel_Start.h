#pragma once
#include "CLevel.h"

class Player;

class GLevel_Start :
    public CLevel
{
private:
	Player* m_Player;

public:
	GLevel_Start();
	virtual ~GLevel_Start() override;

public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void Render() override;
};

