#pragma once
#include "CBase.h"

class CObj;
class Collider;

class CLevel : public CBase
{
private:
	vector<CObj*> m_vecObjects[(UINT)LAYER_TYPE::END];
	vector<Collider*> m_vecCollider[(UINT)LAYER_TYPE::END];

public:
	CLevel();
	virtual ~CLevel();

public:
	// 시점함수
	// Begin		: 레벨이 시작될 때
	// Tick			: 매 프레임마다 Object 들이 수행할 작업
	// FinalTick	: 매 프레임마다 Object 의 Component들이 수행할 작업
	// Render		: 매 프레임마다 Object 가 화면에 그려질 때
	virtual void Begin() = 0;
	virtual void Tick() = 0;
	virtual void FinalTick();
	virtual void Render();
	virtual void End();

public:
	void AddObject(CObj* _Object, LAYER_TYPE _Layer);
	const vector<CObj*>& GetGameObject(LAYER_TYPE _Layer) { return m_vecObjects[(UINT)_Layer]; }
	vector<CObj*>& GetUI() { return m_vecObjects[(UINT)LAYER_TYPE::UI]; }

	void RegisterCollider(Collider * _Collider,LAYER_TYPE _Layer) { m_vecCollider[(UINT)_Layer].push_back(_Collider); }
	const vector<Collider*>& GetCollider(LAYER_TYPE _Layer) { return m_vecCollider[(UINT)_Layer]; }

	CObj* FindGameObject( const wstring& _Name , LAYER_TYPE _Layer = LAYER_TYPE::END);

protected:
	void DeleteObject(int _LayerIdx);
	void DeleteAllObject();
};

