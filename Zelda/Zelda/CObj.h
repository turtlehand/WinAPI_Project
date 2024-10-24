#pragma once
#include "CBase.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

class Collider;
class GComponent;

class CObj : public CBase
{
private:
	Vec2 m_Pos;
	Vec2 m_Scale;
	vector<GComponent*> m_Component;
	LAYER_TYPE m_LayerType;
	bool m_Dead;

public:
	virtual void Awake() {};
	virtual void Begin() = 0;			// 레벨이 시작될 때
	virtual void Tick() = 0;			// 오브젝트가 할 일
	void FinalTick();					// 오브젝트가 소유한 Component가 할 일
	virtual void Render() = 0;			// 오브젝트를 그리기

	virtual void EnterOverlap(Collider* _Collider);
	virtual void Overlap(Collider* _Collider);
	virtual void ExitOverlap(Collider* _Collider);

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetPos(POINT _Pos) { m_Pos = _Pos; }
	void SetPos(float _PosX, float _PosY) { m_Pos = Vec2(_PosX, _PosY); }
	Vec2 GetPos() const { return m_Pos; };
	/// <summary>
	/// 윈도우상에서 현재 위치를 반환한다.
	/// </summary>
	/// <returns></returns>
	Vec2 GetRenderPos() const;

	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	void SetScale(POINT _Scale) { m_Scale = _Scale; }
	void SetScale(float _ScaleX, float _ScaleY) { m_Scale = Vec2(_ScaleX, _ScaleY); }
	Vec2 GetScale() const { return m_Scale; }

	template<typename T>
	T* AddComponent();

	template<typename T>
	T* GetComponent();

	LAYER_TYPE GetLayerType() { return m_LayerType; }

	bool IsDead() const { return m_Dead; }

public:
	CObj();
	virtual ~CObj() override;

	friend class CLevel;
	friend class TaskManager;
};

template<typename T>
T* CObj::AddComponent()
{
	T* _Component = new T;
	_Component->m_Owner = this;
	m_Component.push_back(_Component);
	
	return _Component;
}

template<typename T>
T* CObj::GetComponent()
{
	for (size_t i = 0; i < m_Component.size(); ++i)
	{
		if (dynamic_cast<T*>(m_Component[i]) != nullptr)
			return (T*)m_Component[i];
	}

	return nullptr;
}
