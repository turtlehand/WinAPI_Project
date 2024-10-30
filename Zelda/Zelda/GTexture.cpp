#include "pch.h"
#include "GTexture.h"

#include "CEngine.h"
#include "GPathManager.h"

GTexture::GTexture() :
	GAsset(ASSET_TYPE::TEXTURE),
	m_hBit(nullptr),
	m_DC(nullptr),
	m_BitmapInfo{},
	m_Image(nullptr)
{

}

GTexture::~GTexture()
{
	DeleteDC(m_DC);
	DeleteObject(m_hBit);

	if (nullptr != m_Image)
		delete m_Image;
}

void GTexture::Create(UINT _Width, UINT _Height)
{
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _Width, _Height);

	m_DC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	DeleteObject(SelectObject(m_DC, m_hBit));

	// 비트맵의 정보를 받아온다.
	GetObject(m_hBit, sizeof(BITMAP), &m_BitmapInfo);
}

int GTexture::Save(const wstring& _RelativePath)
{
	return S_OK;
}

int GTexture::Load(const wstring& _RelativePath)
{
	wstring strContent = GPathManager::GetContentPath() + _RelativePath;

	wchar_t ext[50] = {};
	_wsplitpath_s(strContent.c_str(), 0, 0, 0, 0, 0, 0, ext, 50);

	if (!wcscmp(ext, L".bmp") || !wcscmp(ext, L".BMP"))
	{
		// 경로에 존재하는 이미지 파일을 비트맵 형태로 메모리에 로딩
		m_hBit = (HBITMAP)LoadImage(nullptr, strContent.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	}
	else if (!wcscmp(ext, L".png") || !wcscmp(ext, L".PNG"))
	{
		// png 로딩
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gidstartupinput = {};

		GdiplusStartup(&gdiplusToken, &gidstartupinput, nullptr);
		m_Image = Image::FromFile(strContent.c_str(), false);
		Bitmap* pBit = (Bitmap*)m_Image->Clone();

		Status stat = pBit->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);
		if (stat != Status::Ok)
			assert(nullptr);
	}
	else
	{
		assert(false);
	}


	// 비트맵을 타겟으로 지정할 DC 생성
	m_DC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	//비트맵과 DC 연결
	DeleteObject(SelectObject(m_DC, m_hBit));

	// 비트맵의 정보를 받아온다.
	GetObject(m_hBit, sizeof(BITMAP), &m_BitmapInfo);


	return S_OK;
}