#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <map>

/**
 * @class Asset
 * @brief Represents an asset.
 *
 * The Asset class represents an asset. It provides methods to get and set the name of the asset.
 */
class Asset
{
public:
    /**
     * @brief Constructor for the Asset class.
     * @param name The name of the asset.
     */
    Asset(const std::string &name) : _name(name) {}

    /**
     * @brief Destructor for the Asset class.
     */
    ~Asset(void) = default;

    /**
     * @brief Gets the name of the asset.
     * @return The name of the asset.
     */
    const std::string &getName(void) const { return _name; }

    /**
     * @brief Sets the name of the asset.
     * @param name The name of the asset.
     */
    void setName(const std::string &name) { _name = name; }

private:
    std::string _name;
    std::string _file_path;
    std::vector<std::uint8_t> _file_data;
};

class ConfigAsset : public Asset
{
public:
    ConfigAsset(const std::string &name) : Asset(name) {}
    ~ConfigAsset(void) = default;
};

class FontAsset : public Asset
{
public:
    FontAsset(const std::string &name) : Asset(name) {}
    ~FontAsset(void) = default;
};

class ImageAsset : public Asset
{
    ImageAsset(const std::string &name) : Asset(name) {}
    ~ImageAsset(void) = default;
};

class ModelAsset : public Asset
{
    ModelAsset(const std::string &name) : Asset(name) {}
    ~ModelAsset(void) = default;
};

class ShaderAsset : public Asset
{
    ShaderAsset(const std::string &name) : Asset(name) {}
    ~ShaderAsset(void) = default;
};

class SoundAsset : public Asset
{
    SoundAsset(const std::string &name) : Asset(name) {}
    ~SoundAsset(void) = default;
};

enum class AssetType
{
    ConfigAsset,
    FontAsset,
    ImageAsset,
    ModelAsset,
    ShaderAsset,
    SoundAsset
};

static const std::map<std::string, AssetType> asset_type_map = {
    {"configs", AssetType::ConfigAsset},
    {"fonts", AssetType::FontAsset},
    {"images", AssetType::ImageAsset},
    {"models", AssetType::ModelAsset},
    {"shaders", AssetType::ShaderAsset},
    {"sounds", AssetType::SoundAsset}
};