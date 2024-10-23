#include "pch.h"
#include "CLevel.h"
#include "CObj.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (size_t i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		Delete_Vector(m_vecObjects[i]);
	}
}

void CLevel::AddObject(CObj* _Object, LAYER_TYPE _Layer)
{
	m_vecObjects[(UINT)_Layer].push_back(_Object);
	_Object->m_LayerType = _Layer;
}

void CLevel::Begin()
{
	for (size_t i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++i)
		{
			m_vecObjects[i][j]->Begin();
		}
	}

}

void CLevel::Tick()
{
	// 이전 프레임에 등록된 충돌체들을 등록 해제
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_vecCollider[i].clear();
	}

	for (size_t i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->Tick();
		}
	}

}

void CLevel::FinalTick()
{
	for (size_t i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_vecObjects[i].size(); ++j)
		{
			m_vecObjects[i][j]->FinalTick();
		}
	}
}

void CLevel::Render()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		vector<CObj*>& vecObjects = m_vecObjects[i];
		vector<CObj*>::iterator iter = vecObjects.begin();
		for (; iter != vecObjects.end();)
		{
			if ((*iter)->IsDead())
			{
				iter = vecObjects.erase(iter);
			}
			else
			{
				(*iter)->Render();
				++iter;
			}
		}
	}
}

void CLevel::End()
{
	DeleteAllObject();
}

CObj* CLevel::FindGameObject(const wstring& _Name , LAYER_TYPE _Layer)
{
	// 레이어를 지정하지 않는다면 모든 오브젝트를 탐색한다.
	if (_Layer == LAYER_TYPE::END)
	{
		for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
		{
			for (UINT j = 0; j < m_vecObjects[i].size(); ++j)
			{
				if (m_vecObjects[i][j]->GetName() == _Name)
					return m_vecObjects[i][j];
			}
		}
	}
	else
	{
		for (UINT i = 0; i < m_vecObjects[(UINT)_Layer].size(); ++i)
		{
			if (m_vecObjects[(UINT)_Layer][i]->GetName() == _Name)
				return m_vecObjects[(UINT)_Layer][i];
		}
	}

	return nullptr;
}

void CLevel::DeleteObject(int _LayerIdx)
{
	for (size_t i = 0; i < m_vecObjects[_LayerIdx].size(); ++i)
	{
		if (m_vecObjects[_LayerIdx][i]->IsDead())
			continue;

		delete m_vecObjects[_LayerIdx][i];
	}

	m_vecObjects[_LayerIdx].clear();
}

void CLevel::DeleteAllObject()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		DeleteObject(i);
	}
}
