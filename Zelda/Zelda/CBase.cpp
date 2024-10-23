#include "pch.h"
#include "CBase.h"

UINT CBase::g_NextID = 0;

CBase::CBase() :
	m_ID(g_NextID++)
{
}

CBase::~CBase()
{
}

CBase::CBase(const CBase& _Origin) :
	m_Name(_Origin.m_Name),
	m_ID(g_NextID++)
{

}

// const가 붙은 클래스는 대입연산자가 생성되지 않는다.
CBase& CBase::operator=(const CBase& _Origin)
{
	m_Name = _Origin.m_Name;
	return *this;
}
