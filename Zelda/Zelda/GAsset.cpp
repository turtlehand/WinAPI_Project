#include "pch.h"
#include "GAsset.h"

GAsset::GAsset(ASSET_TYPE _Type) :
	m_Type(_Type)
{
}

GAsset::~GAsset()
{
}

void GAsset::CheckExt(const wstring& _Ext, wstring& _strFilePath)
{
	wchar_t szExt[50] = {};

	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);
	// Ȯ���ڰ� �ùٸ��� �ʴٸ�
	if (wcscmp(szExt, _Ext.c_str()))
	{
		// Ȯ���ڰ� ���õǾ����� �ʾҴٸ�
		if (!wcscmp(szExt, L""))
		{
			_strFilePath += _Ext;
		}
		else
		{
			_strFilePath = _strFilePath.substr(0, _strFilePath.find(szExt));
			_strFilePath += _Ext;
		}
	}
}