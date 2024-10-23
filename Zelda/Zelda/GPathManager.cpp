#include "pch.h"
#include "GPathManager.h"

wchar_t GPathManager::g_ContentPath[255] = {};
wchar_t GPathManager::g_BinPath[255] = {};
wchar_t GPathManager::g_SolutionPath[255] = {};

void GPathManager::Init()
{
	wchar_t szBuff[255] = {};
	wchar_t szBuffCopy[255] = {};

	// ���� ���μ����� ���(����� ���� ������ ��� ����ó�� �ʿ�, ������Ʈ ����->Debug->�۾����͸� ����)
	GetCurrentDirectory(255, szBuff);

	for (int i = wcslen(szBuff); 0 <= i; --i)
	{
		if (L'\\' == szBuff[i])
		{
			szBuff[i] = L'\0';
			break;
		}
	}

	wcscpy_s(szBuffCopy, 255, szBuff);

	wcscat_s(szBuffCopy, 255, L"\\Content\\");
	wcscpy_s(g_ContentPath, 255, szBuffCopy);


	wcscpy_s(szBuffCopy, 255, szBuff);

	wcscat_s(szBuffCopy, 255, L"\\bin\\");
	wcscpy_s(g_BinPath, 255, szBuffCopy);
}