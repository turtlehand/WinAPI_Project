#pragma once
#include "CBase.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

class GCollider;
class GComponent;

class CObj : public CBase
{
private:
	CObj* m_Parent;
	vector<CObj*> m_vecChild;

	Vec2 m_Pos;
	Vec2 m_Scale;
	vector<GComponent*> m_Component;
	LAYER_TYPE m_LayerType;
	bool m_PrevActive;
	bool m_Active;
	bool m_Dead;


public:
	virtual void Awake() {};
	virtual void Begin() = 0;			// ������ ���۵� ��
	virtual void Tick() = 0;			// ������Ʈ�� �� ��
	void FinalTick();					// ������Ʈ�� ������ Component�� �� ��
	virtual void OnEnable() {};			// ������Ʈ�� Ȱ��ȭ �� ��
	virtual void OnDisable() {};		// ������Ʈ�� ��Ȱ��ȭ �� ��
	virtual void Render() = 0;			// ������Ʈ�� �׸���

	virtual void EnterOverlap(GCollider* _Collider);
	virtual void Overlap(GCollider* _Collider);
	virtual void ExitOverlap(GCollider* _Collider);

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetPos(POINT _Pos) { m_Pos = _Pos; }
	void SetPos(float _PosX, float _PosY) { m_Pos = Vec2(_PosX, _PosY); }
	Vec2 GetPos() const { return m_Pos; };
	/// <summary>
	/// ������󿡼� ���� ��ġ�� ��ȯ�Ѵ�.
	/// </summary>
	/// <returns></returns>
	Vec2 GetRenderPos();

	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }
	void SetScale(POINT _Scale) { m_Scale = _Scale; }
	void SetScale(float _ScaleX, float _ScaleY) { m_Scale = Vec2(_ScaleX, _ScaleY); }
	Vec2 GetScale() const { return m_Scale; }

	void SetActive(bool _Active);
	bool GetActive() { return m_Active; }

	void SetParent(CObj* _Parent);
	void AddChild(CObj* _Child) {
		m_vecChild.push_back(_Child);
		_Child->m_Parent = this;
	}

	template<typename T>
	T* GetChildObj();

	Vec2 GetGlobalPos() {
		if (m_Parent)
			return m_Parent->GetGlobalPos() + this->GetPos();
		return this->GetPos();
	}

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
	friend class GUIManager;
	friend class GUI;
};

template<typename T>
T* CObj::GetChildObj()
{
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		if (dynamic_cast<T*>(m_vecChild[i]) != nullptr)
			return (T*)m_vecChild[i];
	}
	return nullptr;
}

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
