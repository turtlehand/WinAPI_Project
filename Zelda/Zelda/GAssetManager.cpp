#include "pch.h"
#include "GAssetManager.h"

#include "GTexture.h"
#include "GSprite.h"
#include "GFlipBook.h"
#include "GSound.h"

GAssetManager::GAssetManager()
{

}

GAssetManager::~GAssetManager()
{
	Delete_Map(m_mapTexture);
	Delete_Map(m_mapSprite);
	Delete_Map(m_mapFlipBook);
	Delete_Map(m_mapSound);
}

void GAssetManager::Init()
{

}


#pragma region Texture

GTexture* GAssetManager::FindTexture(const wstring& _Key)
{
	map<wstring, GTexture*>::iterator iter = m_mapTexture.find(_Key);

	if (iter == m_mapTexture.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

GTexture* GAssetManager::LoadTexture(const wstring& _Key, const wstring& _RelativePath)
{
	GAsset* pTexture = FindTexture(_Key);
	if (pTexture != nullptr)
	{
		return (GTexture*)pTexture;
	}

	pTexture = new GTexture;
	pTexture->Load(_RelativePath);

	// 에셋에, 자신이 에셋매니저에 등록될 때 사용된 키값과 로딩할 때 사용할 경로를 세팅해준다.
	pTexture->SetKey(_Key);
	pTexture->SetRelativePath(_RelativePath);

	// 컨테이너에 텍스쳐 등록
	m_mapTexture.insert(make_pair(_Key, (GTexture*)pTexture));

	return (GTexture*)pTexture;
}

GTexture* GAssetManager::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height)
{
	GTexture* pTex = FindTexture(_Key);
	assert(!pTex);

	pTex = new GTexture;
	pTex->Create(_Width, _Height);

	// 에셋에, 자신이 에셋매니저에 등록될 때 사용된 키 값을 세팅해준다.
	pTex->SetKey(_Key);

	// 컨테이너에 텍스쳐 등록
	m_mapTexture.insert(make_pair(_Key, (GTexture*)pTex));
	return pTex;
}


#pragma endregion

#pragma region Sprite

GSprite* GAssetManager::FindSprite(const wstring& _Key)
{
	map<wstring, GSprite*>::iterator iter = m_mapSprite.find(_Key);

	if (iter == m_mapSprite.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

GSprite* GAssetManager::LoadSprite(const wstring& _Key, const wstring& _RelativePath)
{
	GAsset* pSprite = FindSprite(_Key);
	if (pSprite != nullptr)
	{
		return (GSprite*)pSprite;
	}

	pSprite = new GSprite;
	pSprite->Load(_RelativePath);

	// 에셋에, 자신이 에셋매니저에 등록될 때 사용된 키값과 로딩할 때 사용할 경로를 세팅해준다.
	pSprite->SetKey(_Key);
	pSprite->SetRelativePath(_RelativePath);

	// 컨테이너에 스프라이트 등록
	m_mapSprite.insert(make_pair(_Key, (GSprite*)pSprite));

	return (GSprite*)pSprite;
}

void GAssetManager::AddSprite(const wstring& _Key, GSprite* _Sprite)
{
	// Sprite가 없다면 중지
	assert(!FindSprite(_Key));

	// 스프라이트에 키를 설정해주고 컨테이너에 스프라이트 등록
	_Sprite->SetKey(_Key);
	m_mapSprite.insert(make_pair(_Key, _Sprite));
}


#pragma endregion

#pragma region FlipBook

GFlipBook* GAssetManager::FindFlipBook(const wstring& _Key)
{
	map<wstring, GFlipBook*>::iterator iter = m_mapFlipBook.find(_Key);

	if (iter == m_mapFlipBook.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

GFlipBook* GAssetManager::LoadFlipBook(const wstring& _Key, const wstring& _RelativePath)
{
	GAsset* pFlipBook = FindFlipBook(_Key);
	if (pFlipBook != nullptr)
	{
		return (GFlipBook*)pFlipBook;
	}

	pFlipBook = new GFlipBook;
	pFlipBook->Load(_RelativePath);

	// 에셋에, 자신이 에셋매니저에 등록될 때 사용된 키값과 로딩할 때 사용할 경로를 세팅해준다.
	pFlipBook->SetKey(_Key);
	pFlipBook->SetRelativePath(_RelativePath);

	// 컨테이너에 플립북 등록
	m_mapFlipBook.insert(make_pair(_Key, (GFlipBook*)pFlipBook));

	return (GFlipBook*)pFlipBook;
}

void GAssetManager::AddFlipBook(const wstring& _Key, GFlipBook* _FlipBook)
{
	assert(!FindFlipBook(_Key));

	_FlipBook->SetKey(_Key);
	m_mapFlipBook.insert(make_pair(_Key, _FlipBook));
}


#pragma endregion

#pragma region Sound


GSound* GAssetManager::FindSound(const wstring& _Key)
{
	map<wstring, GSound*>::iterator iter = m_mapSound.find(_Key);

	if (iter == m_mapSound.end())
		return nullptr;

	return (*iter).second;
}

GSound* GAssetManager::LoadSound(const wstring& _Key, const wstring& _RelativePath)
{
	GAsset* pSound = (GSound*)FindSound(_Key);

	if (pSound != nullptr)
		return (GSound*)pSound;

	pSound = new GSound;
	pSound->Load(_RelativePath);

	pSound->SetKey(_Key);
	pSound->SetRelativePath(_RelativePath);

	m_mapSound.insert(make_pair(_Key, (GSound*)pSound));

	return (GSound*)pSound;
}


#pragma endregion

