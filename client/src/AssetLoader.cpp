#include "AssetLoader.hpp"

#include <filesystem>
#include <iostream>

void AssetLoader::loadAssets(void)
{
    std::filesystem::path asset_directory_path(_asset_directory_path);

    for (const auto &entry : std::filesystem::directory_iterator(asset_directory_path))
    {
        std::cout << entry.path() << std::endl;
    }
}