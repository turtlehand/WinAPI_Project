#pragma once
#include "GAsset.h"

class GTexture : public GAsset
{
private:
	HBITMAP		m_hBit;					// ��Ʈ�� �ڵ�
	HDC			m_DC;					// ��Ʈ���� �������� �����ϴ� DC
	BITMAP		m_BitmapInfo;			// ��Ʈ�� ����

	Image* m_Image;

public:
	HDC GetDC() { return m_DC; }
	UINT GetWidth() { return m_BitmapInfo.bmWidth; }
	UINT GetHeight() { return m_BitmapInfo.bmHeight; }

private:
	void Create(UINT _Width, UINT _Height);
	virtual int Save(const wstring& _RelativePath) override;
	virtual int Load(const wstring& _FilePath) override;
public:
	GTexture();
	virtual ~GTexture() override;

	friend class GAssetManager;
};

