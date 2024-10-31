#include "pch.h"
#include "GAssetManager.h"

#include "GTexture.h"
#include "GSprite.h"
#include "GFlipBook.h"
#include "GSound.h"
#include "GTile.h"
#include "GTilePalette.h"

GAssetManager::GAssetManager()
{

}

GAssetManager::~GAssetManager()
{
	Delete_Map(m_mapTexture);
	Delete_Map(m_mapSprite);
	Delete_Map(m_mapFlipBook);
	Delete_Map(m_mapSound);
	Delete_Map(m_mapTile);
	Delete_Map(m_mapTilePalette);
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

	// ���¿�, �ڽ��� ���¸Ŵ����� ��ϵ� �� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
	pTexture->SetKey(_Key);
	pTexture->SetRelativePath(_RelativePath);

	// �����̳ʿ� �ؽ��� ���
	m_mapTexture.insert(make_pair(_Key, (GTexture*)pTexture));

	return (GTexture*)pTexture;
}

GTexture* GAssetManager::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height)
{
	GTexture* pTex = FindTexture(_Key);
	assert(!pTex);

	pTex = new GTexture;
	pTex->Create(_Width, _Height);

	// ���¿�, �ڽ��� ���¸Ŵ����� ��ϵ� �� ���� Ű ���� �������ش�.
	pTex->SetKey(_Key);

	// �����̳ʿ� �ؽ��� ���
	m_mapTexture.insert(make_pair(_Key, (GTexture*)pTex));
	return pTex;
}

int GAssetManager::DeleteTexture(const wstring& _Key)
{
	GTexture* pTex = FindTexture(_Key);
	assert(pTex != nullptr);

	m_mapTexture.erase(_Key);
	delete pTex;

	pTex = nullptr;

	return S_OK;
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

	// ���¿�, �ڽ��� ���¸Ŵ����� ��ϵ� �� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
	pSprite->SetKey(_Key);
	pSprite->SetRelativePath(_RelativePath);

	// �����̳ʿ� ��������Ʈ ���
	m_mapSprite.insert(make_pair(_Key, (GSprite*)pSprite));

	return (GSprite*)pSprite;
}

void GAssetManager::AddSprite(const wstring& _Key, GSprite* _Sprite)
{
	// Sprite�� �ִٸ� ����
	assert(!FindSprite(_Key));

	// ��������Ʈ�� Ű�� �������ְ� �����̳ʿ� ��������Ʈ ���
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

	// ���¿�, �ڽ��� ���¸Ŵ����� ��ϵ� �� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
	pFlipBook->SetKey(_Key);
	pFlipBook->SetRelativePath(_RelativePath);

	// �����̳ʿ� �ø��� ���
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

#pragma region Tile

GTile* GAssetManager::FindTile(const wstring& _Key)
{
	map<wstring, GTile*>::iterator iter = m_mapTile.find(_Key);

	if (iter == m_mapTile.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

GTile* GAssetManager::LoadTile(const wstring& _Key, const wstring& _RelativePath)
{
	GAsset* pTile = FindTile(_Key);
	if (pTile != nullptr)
	{
		return (GTile*)pTile;
	}

	pTile = new GTile;
	pTile->Load(_RelativePath);

	// ���¿�, �ڽ��� ���¸Ŵ����� ��ϵ� �� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
	pTile->SetKey(_Key);
	pTile->SetRelativePath(_RelativePath);

	// �����̳ʿ� Ÿ�� ���
	m_mapTile.insert(make_pair(_Key, (GTile*)pTile));

	return (GTile*)pTile;
}

GTile* GAssetManager::CreateTile(const wstring& _Key, const wstring& _RelativePath, GSprite* _Sprite)
{
	GTile* pTile = FindTile(_Key);
	assert(!pTile);

	pTile = new GTile;
	pTile->Create(_Sprite);

	// ���¿�, �ڽ��� ���¸Ŵ����� ��ϵ� �� ���� Ű ���� �������ش�.
	pTile->SetKey(_Key);
	pTile->SetRelativePath(_RelativePath);

	// �����̳ʿ� �ؽ��� ���
	m_mapTile.insert(make_pair(_Key, (GTile*)pTile));
	pTile->Save(_RelativePath + _Key);
	return pTile;

	return nullptr;
}

#pragma endregion

#pragma region TilePalette

GTilePalette* GAssetManager::FindTilePalette(const wstring& _Key)
{
	map<wstring, GTilePalette*>::iterator iter = m_mapTilePalette.find(_Key);

	if (iter == m_mapTilePalette.end())
	{
		return nullptr;
	}
	return (*iter).second;
}

GTilePalette* GAssetManager::LoadTilePalette(const wstring& _Key, const wstring& _RelativePath)
{
	GAsset* pTilePalette = FindTilePalette(_Key);
	if (pTilePalette != nullptr)
	{
		return (GTilePalette*)pTilePalette;
	}

	pTilePalette = new GTilePalette;
	pTilePalette->Load(_RelativePath);

	// ���¿�, �ڽ��� ���¸Ŵ����� ��ϵ� �� ���� Ű���� �ε��� �� ����� ��θ� �������ش�.
	pTilePalette->SetKey(_Key);
	pTilePalette->SetRelativePath(_RelativePath);

	// �����̳ʿ� Ÿ���ȷ�Ʈ ���
	m_mapTilePalette.insert(make_pair(_Key, (GTilePalette*)pTilePalette));

	return (GTilePalette*)pTilePalette;
}

#pragma endregion





