#pragma once

// �߻� Ŭ������ ������ ��
class CBase
{
	static UINT g_NextID;

private:
	wstring m_Name;
	const UINT m_ID;


public:
	// inline Ű���� or ����� �Լ��� ������ ��� --> inline �Լ�
	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() { return m_Name; }

	const UINT& GetID() { return m_ID; }

public:
	CBase();
	virtual ~CBase() = 0;

	CBase(const CBase& _Origin);

public:
	CBase& operator=(const CBase& _Origin);

};

