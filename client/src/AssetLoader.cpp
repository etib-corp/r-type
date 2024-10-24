#include "AssetLoader.hpp"

#include <filesystem>
#include <iostream>

AssetLoader::AssetLoader(std::shared_ptr<AssetManager> asset_manager, const std::string &asset_directory_path) : _asset_manager(asset_manager), _asset_directory_path(asset_directory_path) {
    _asset_factory = std::make_unique<AssetFactory>();

    _asset_factory->registerAsset("configs", [](std::string name, std::string file_path) {
        return std::make_shared<ConfigAsset>(name, file_path);
    });

    _asset_factory->registerAsset("fonts", [](std::string name, std::string file_path) {
        return std::make_shared<FontAsset>(name, file_path);
    });

    _asset_factory->registerAsset("images", [](std::string name, std::string file_path) {
        return std::make_shared<ImageAsset>(name, file_path);
    });

    _asset_factory->registerAsset("models", [](std::string name, std::string file_path) {
        return std::make_shared<ModelAsset>(name, file_path);
    });
    
    _asset_factory->registerAsset("shaders", [](std::string name, std::string file_path) {
        return std::make_shared<ShaderAsset>(name, file_path);
    });

    _asset_factory->registerAsset("sounds", [](std::string name, std::string file_path) {
        return std::make_shared<SoundAsset>(name, file_path);
    });
}

void AssetLoader::loadAssets(void)
{
    std::filesystem::path asset_directory_path(_asset_directory_path);
    std::string sub_directory_name;
    std::filesystem::path sub_asset_directory_path;
    std::string asset_name;
    std::string asset_file_path;
    std::shared_ptr<Asset> asset;

    for (const auto &entry : std::filesystem::directory_iterator(asset_directory_path))
    {
        sub_directory_name = entry.path().filename().string();
        sub_asset_directory_path = entry.path();
        
        for (const auto &sub_entry : std::filesystem::directory_iterator(sub_asset_directory_path))
        {
            asset_name = sub_entry.path().filename().string();
            asset_file_path = _asset_directory_path + "/" + sub_directory_name + "/" + asset_name;
            try {
                asset = _asset_factory->createAsset(sub_directory_name, asset_name, asset_file_path);
            } catch (const std::runtime_error &e) {
                std::cerr << "Error: " << e.what() << std::endl;
                continue;
            }
            asset->load();
            _asset_manager->addAsset(asset);
        }
    }
}
