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
     * @brief Retrieves an asset from the asset manager.
     * @param name The name of the asset.
     * @return A unique pointer to the asset.
     * @throws std::runtime_error if the asset is not found.
     */
    std::unique_ptr<Asset> &getAsset(const std::string &name);

    /**
     * @brief Adds an asset to the asset manager.
     * @param asset The asset to add.
     */
    void addAsset(std::unique_ptr<Asset> asset);

    /**
     * @brief Removes an asset from the asset manager.
     * @param name The name of the asset.
     */
    void removeAsset(const std::string &name);

private:
    std::map<std::string, std::unique_ptr<Asset>> _assets;
};
