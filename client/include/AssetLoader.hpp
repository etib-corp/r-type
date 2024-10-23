#pragma once

#include <memory>

#include "AssetManager.hpp"

class AssetLoader
{
public:
    /**
     * @brief Constructor for the AssetLoader class.
     * @param asset_manager The asset manager.
     * @param asset_directory_path The path to the asset directory.
     */
    AssetLoader(std::shared_ptr<AssetManager> asset_manager, const std::string &asset_directory_path) : _asset_manager(asset_manager), _asset_directory_path(asset_directory_path) {}

    /**
     * @brief Destructor for the AssetLoader class.
     */
    ~AssetLoader(void) = default;

    /**
     * @brief Loads an asset from the asset manager.
     */
    void loadAssets(void);

private:
    std::shared_ptr<AssetManager> _asset_manager;
    std::string _asset_directory_path;
};
