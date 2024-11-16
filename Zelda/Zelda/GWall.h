#pragma once
#include "CObj.h"

class SpriteRenderer;

class GWall : public CObj
{
public:
	virtual void Awake() override;
	virtual void Tick() override {};
	virtual void Render() override ;

public:
	GWall();
	virtual ~GWall() override;
};

