#pragma once
#include "CObj.h"

class GWall : public CObj
{
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void Render() override {};

public:
	GWall();
	virtual ~GWall() override;
};

