#include "AssetLoader.hpp"

#include <filesystem>
#include <iostream>

void AssetLoader::loadAssets(void)
{
    std::filesystem::path asset_directory_path(_asset_directory_path);

    for (const auto &entry : std::filesystem::directory_iterator(asset_directory_path))
    {
        auto sub_directory_name = entry.path().filename().string();
        auto asset_type = asset_type_map.at(sub_directory_name);
        auto sub_asset_directory_path = entry.path();
        for (const auto &sub_entry : std::filesystem::directory_iterator(sub_asset_directory_path))
        {
            auto asset_name = sub_entry.path().filename().string();
            auto asset = std::make_shared<Asset>(asset_name);
            _asset_manager->addAsset(asset);
            std::cout << "Added asset: " << asset_name << " of type: " << sub_directory_name << std::endl;
        }
    }
}