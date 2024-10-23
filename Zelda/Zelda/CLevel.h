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
	// �����Լ�
	// Begin		: ������ ���۵� ��
	// Tick			: �� �����Ӹ��� Object ���� ������ �۾�
	// FinalTick	: �� �����Ӹ��� Object �� Component���� ������ �۾�
	// Render		: �� �����Ӹ��� Object �� ȭ�鿡 �׷��� ��
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

