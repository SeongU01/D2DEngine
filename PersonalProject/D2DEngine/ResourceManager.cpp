#include "pch.h"
#include "ResourceManager.h"
#include "AnimationAsset.h"


std::unique_ptr<ResourceManager> ResourceManager::_pInstance(nullptr);


ResourceManager::ResourceManager(std::shared_ptr<D2DRenderer> renderer)
  : _pRenderer(renderer)
{
}

ResourceManager::~ResourceManager()
{
  for (auto& iter : _images)
  {
    if (iter.second)
      iter.second->Release();
  }
  for (auto& iter : _anims)
  {
    delete iter.second;
  }
}

bool ResourceManager::LoadImages(const std::wstring& szPath)
{
  if (!_pRenderer)
  {
    throw std::runtime_error("Renderer is nullptr!");
  }

  if (szPath.empty())
  {
    throw std::runtime_error("szPath is empty in LoadImage!");
  }

  ID2D1Bitmap* pBitmap = nullptr;

  _pRenderer->CreateD2DBitmapFromFile(szPath.c_str(), &pBitmap);

  if (pBitmap != nullptr)
  {
    _images[szPath] = pBitmap;
    return true;
  }

  return false;
}

bool ResourceManager::CreateAnimAsset(std::wstring strFilePath, AnimationAsset** asset)
{
  if (_anims.find(strFilePath) != _anims.end())
  {
    *asset = _anims[strFilePath];
    (*asset)->AddRef();
    return true;
  }

  AnimationAsset* pTemp = new AnimationAsset;
  // 생성한 애니메이션 에셋에 애니메이션 데이터를 로드한다.
  if (pTemp->LoadAnimation(strFilePath) == false)
  {
    delete pTemp;
    throw std::runtime_error("Failed to load animation from file: " + WStringToString(strFilePath));
  }
  else
  {
    *asset = pTemp;
    (*asset)->AddRef();
  }
  // 생성한 애니메이션 에셋을 맵에 저장한다.
  _anims[strFilePath] = *asset;
  return true;
}

void ResourceManager::ReleaseAnimAsset(std::wstring strFilePath)
{
  // 맵에 해당 키가 존재하면 애니메이션 에셋을 해제한다.
  auto iter = _anims.find(strFilePath);

  if (iter == _anims.end())
  {
    throw std::runtime_error("Animation asset to release not found for file: " + WStringToString(strFilePath));
  }

  AnimationAsset* asset = _anims[strFilePath];
  if (asset->Release() == 0)
  {
    _anims.erase(iter);
  }
}

ID2D1Bitmap* ResourceManager::GetImage(const std::wstring& szPath)
{
  if (szPath.empty())
  {
    throw std::runtime_error("szPath is empty!");
  }

  auto iter = _images.find(szPath);
  if (iter != _images.end())
  {
    auto sharedPtr = iter->second;
    if (sharedPtr)
    {
      return sharedPtr;
    }
    else
    {
      _images.erase(iter);
    }
  }

  if (LoadImages(szPath))
  {
    auto sharedPtr = _images[szPath];
    if (sharedPtr)
    {
      return sharedPtr;
    }
  }

  throw std::runtime_error("Failed to get image from resource file: " + WStringToString(szPath));
}

ResourceManager& ResourceManager::Create(std::shared_ptr<D2DRenderer> renderer)
{
  if (_pInstance)
  {
    throw std::runtime_error("Recreation of ResourceManager detected!");
  }
  _pInstance.reset(new ResourceManager(renderer));
  return *_pInstance;
}

void ResourceManager::Destroy()
{
  if (!_pInstance)
  {
    throw std::runtime_error("Destruction of uninitialized ResourceManager detected!");
  }

  _pInstance.reset();
}

ResourceManager& ResourceManager::Get()
{
  if (!_pInstance)
  {
    throw std::runtime_error("Access of uninitialized ResourceManager detected!");
  }
  return *_pInstance;
}
