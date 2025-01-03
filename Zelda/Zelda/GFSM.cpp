#include "pch.h"
#include "GFSM.h"

#include "GState.h"

const wstring& GFSM::GetCurrentState()
{
	return m_CurState->GetName();
}

void GFSM::AddState(const wstring& _Key, GState* _State)
{
	assert(FindState(_Key) == nullptr);

	m_mapState.insert(make_pair(_Key, _State));
	_State->m_Owner = this;
	_State->SetName(_Key);
	_State->Awake();
}

GState* GFSM::FindState(const wstring& _Key)
{
	map<wstring, GState*>::iterator iter = m_mapState.find(_Key);

	if (iter == m_mapState.end())
		return nullptr;
	return iter->second;
}

void GFSM::ChanageState(const wstring& _Key)
{
	GState* pNextState = FindState(_Key);
	assert(pNextState != nullptr);

	if(m_CurState != nullptr)
		m_CurState->Exit();

	
	m_CurState = pNextState;
	m_CurState->Enter();
}

void GFSM::FinalTick()
{
	if (m_CurState == nullptr)
		return;
	m_CurState->FinalTick();
}

GFSM::GFSM() :
	GComponent(COMPONENT_TYPE::FSM),
	m_mapState{},
	m_CurState(nullptr)
{
}

GFSM::~GFSM()
{
	Delete_Map(m_mapState);
}
