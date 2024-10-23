#pragma once
#include "CBase.h"

class GAsset : public CBase
{
private:
	wstring m_Key;
	wstring m_RelativePath;
	const ASSET_TYPE m_Type;
public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }
	const ASSET_TYPE GetAssetType() { return m_Type; }
	
protected:
	void CheckExt(const wstring& _Ext, wstring& _strFilePath);
	void SetKey(const wstring& _Key) { m_Key = _Key; }
	void SetRelativePath(const wstring& _RelativePath) { m_RelativePath = _RelativePath; }

public:
	virtual int Save(const wstring& _RelativePath) { return S_OK; }
	virtual int Load(const wstring& _FilePath) = 0;

public:
	GAsset(ASSET_TYPE _Type);
	virtual ~GAsset() override;

	friend class GAssetManager;
};

