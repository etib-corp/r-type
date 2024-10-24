#pragma once

#include <map>

#include "Asset.hpp"

class AssetManager
{
public:
    /**
     * @brief Constructor for the AssetManager class.
     */
    AssetManager(void) = default;

    /**
     * @brief Destructor for the AssetManager class.
     */
    ~AssetManager(void) = default;

    /**
     * @brief Adds an asset to the asset manager.
     * @param asset The asset to add.
     */
    void addAsset(std::shared_ptr<Asset> asset);

    /**
     * @brief Removes an asset from the asset manager.
     * @param name The name of the asset.
     */
    void removeAsset(const std::string &name);

    /**
     * @brief Gets an asset from the asset manager.
     * @param name The name of the asset.
     * @return The asset.
     */
    template <typename AssetType>
    std::shared_ptr<AssetType> getAsset(const std::string &name) {
        return std::dynamic_pointer_cast<AssetType>(_assets[name]);
    }

private:
    std::map<std::string, std::shared_ptr<Asset>> _assets;
};
