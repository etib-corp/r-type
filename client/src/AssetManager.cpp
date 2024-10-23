#include "AssetManager.hpp"

std::shared_ptr<Asset> &AssetManager::getAsset(const std::string &name)
{
    auto asset = _assets.find(name);
    if (asset == _assets.end())
    {
        throw std::runtime_error("Asset not found");
    }
    return asset->second;
}

void AssetManager::addAsset(std::shared_ptr<Asset> asset)
{
    _assets[asset->getName()] = std::move(asset);
}

void AssetManager::removeAsset(const std::string &name)
{
    _assets.erase(name);
}
