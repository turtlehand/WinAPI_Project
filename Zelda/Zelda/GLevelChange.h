#pragma once
#include "CObj.h"

class GLevelChange :
	public CObj
{
private:
	LEVEL_TYPE m_ChanageLevel;

public:
	void SetChanageLevel(LEVEL_TYPE _ChangeLevel) { m_ChanageLevel = _ChangeLevel; }

public:
	virtual void Awake() override;
	virtual void Tick() override {};
	virtual void Render() override;

	virtual void OnTriggerEnter(GCollider* _Collider) override;

public:
	GLevelChange();
	virtual ~GLevelChange() override;
};
