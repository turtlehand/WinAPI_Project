#pragma once
#include "GArrow.h"

class CObj;

class GuidedMissile : public GArrow
{
private:
	CObj* m_Target;
	float m_DetectRange;

public:
	virtual void Tick() override;
	virtual void Render() override;

public:
	void SetDetectRange(float _DetectRange) { m_DetectRange = _DetectRange; }

private:
	void FindTarget();
	void TraceTarget_Direct();
	void TraceTarget_Rotate();
	void TraceTarget_Accel();


public:
	GuidedMissile();
	virtual ~GuidedMissile() override;
};

