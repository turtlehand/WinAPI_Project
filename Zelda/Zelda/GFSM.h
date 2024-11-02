#pragma once
#include "GComponent.h"

class GState;

class GFSM : public GComponent
{
private:
	map<wstring, GState*> m_mapState;
	GState* m_CurState;
public:
	const wstring& GetCurrentState();
	void AddState(const wstring& K_Keyey, GState* _State);
	GState* FindState(const wstring& _Key);
	void ChanageState(const wstring& _Key);

public:
	void FinalTick();

public:
	GFSM();
	virtual ~GFSM() override;
};

