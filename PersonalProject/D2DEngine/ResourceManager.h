#pragma once
#include <unordered_map>
#include <memory>
#include "D2DRenderer.h"

class AnimationAsset;

class ResourceManager
{
public:
	ResourceManager(std::shared_ptr<D2DRenderer> renderer);
	~ResourceManager();

	//sharedptr 공유
	//그냥ptr 공유
	ID2D1Bitmap* GetImage(const std::wstring& szPath);
	bool LoadImages(const std::wstring& szPath);
	bool CreateAnimAsset(std::wstring strFilePath, AnimationAsset** asset);
	void ReleaseAnimAsset(std::wstring strFilePath);
	//unique ptr instance->auto memory delete
private:
	using ImageName = std::wstring;
	std::unordered_map<ImageName, ID2D1Bitmap*> _images;
	std::unordered_map<std::wstring, AnimationAsset*>_anims;

	static std::unique_ptr<ResourceManager> _pInstance;
	std::shared_ptr<D2DRenderer> _pRenderer;
public:
	static ResourceManager& Create(std::shared_ptr<D2DRenderer> renderer);
	static void Destroy();
	static ResourceManager& Get();

};

