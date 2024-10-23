#pragma once

// 추상 클래스로 만들어야 함
class CBase
{
	static UINT g_NextID;

private:
	wstring m_Name;
	const UINT m_ID;


public:
	// inline 키워드 or 헤더에 함수가 구현될 경우 --> inline 함수
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

