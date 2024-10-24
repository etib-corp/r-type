#include "AssetManager.hpp"

void AssetManager::addAsset(std::shared_ptr<Asset> asset)
{
    _assets[asset->getName()] = std::move(asset);
}

void AssetManager::removeAsset(const std::string &name)
{
    _assets.erase(name);
}
