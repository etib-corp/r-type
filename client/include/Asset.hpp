#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

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
    Asset(std::string name, std::string file_path) : _name(name), _file_path(file_path) {}

    /**
     * @brief Destructor for the Asset class.
     */
    virtual ~Asset(void) = default;

    /**
     * @brief Gets the name of the asset.
     * @return The name of the asset.
     */
    const std::string &getName(void) const { return _name; }

    /**
     * @brief Gets the file path of the asset.
     * @return The file path of the asset.
     */
    const std::string getFilePath(void) const { return _file_path; }

    /**
     * @brief Loads the asset.
     */
    virtual void load(void) = 0;

protected:
    std::string _name;
    std::string _file_path;

    std::string _read_file(std::string file_path) {
        std::ifstream file(file_path);

        if (!file.is_open())
            throw std::runtime_error("Failed to open file");

        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    std::vector<std::uint8_t> _read_file_binary(std::string file_path) {
        std::ifstream file(file_path, std::ios::binary);

        if (!file.is_open())
            throw std::runtime_error("Failed to open file");

        return std::vector<std::uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }
};

class ConfigAsset : public Asset
{
public:
    ConfigAsset(std::string name, std::string file_path) : Asset(name, file_path)
    {
        if (!_file_path.ends_with(".json"))
            throw std::runtime_error("Unsupported file format");
    }
    ~ConfigAsset(void) override = default;

    void load(void) override
    {
        _config_data = _read_file(_file_path);
    }

private:
    std::string _config_data;
};

class FontAsset : public Asset
{
public:
    FontAsset(std::string name, std::string file_path) : Asset(name, file_path)
    {
        if (!_file_path.ends_with(".TTF"))
            throw std::runtime_error("Unsupported file format");
    }
    ~FontAsset(void) override = default;

    void load(void) override
    {
        _font_data = _read_file_binary(_file_path);
    }

private:
    std::vector<std::uint8_t> _font_data;
};

class ImageAsset : public Asset
{
public:
    ImageAsset(std::string name, std::string file_path) : Asset(name, file_path)
    {
        if (!_file_path.ends_with(".png"))
            throw std::runtime_error("Unsupported file format");
    }
    ~ImageAsset(void) override = default;

    void load(void) override
    {
        _image_data = _read_file_binary(_file_path);
    }

private:
    std::vector<std::uint8_t> _image_data;
};

class ModelAsset : public Asset
{
public:
    ModelAsset(std::string name, std::string file_path) : Asset(name, file_path)
    {
        std::string material_file = _get_material_file_path();

        if (!_file_path.ends_with(".obj"))
            throw std::runtime_error("Unsupported file format");

        if (!std::filesystem::exists(material_file))
            throw std::runtime_error("Material file not found");
    }
    ~ModelAsset(void) override = default;

    void load(void) override
    {
        std::string material_file = _get_material_file_path();

        _model_data = _read_file(_file_path);
        _material_data = _read_file(material_file);
    }

private:
    std::string _model_data;
    std::string _material_data;

    std::string _get_material_file_path(void) {
        return _file_path.substr(0, _file_path.find_last_of('.')) + ".mtl";
    }
};

class ShaderAsset : public Asset
{
public:
    ShaderAsset(std::string name, std::string file_path) : Asset(name, file_path)
    {
        std::string vertice_file = _get_vertice_file_path();

        if (!_file_path.ends_with(".frag"))
            throw std::runtime_error("Unsupported file format");

        if (!std::filesystem::exists(vertice_file))
            throw std::runtime_error("Vertice file not found");
    }
    ~ShaderAsset(void) override = default;

    void load(void) override
    {
        std::string vertice_file = _get_vertice_file_path();

        _fragment_data = _read_file(_file_path);
        _vertice_data = _read_file(vertice_file);
    }

private:
    std::string _fragment_data;
    std::string _vertice_data;

    std::string _get_vertice_file_path(void) {
        return _file_path.substr(0, _file_path.find_last_of('.')) + ".vert";
    }
};

class SoundAsset : public Asset
{
public:
    SoundAsset(std::string name, std::string file_path) : Asset(name, file_path)
    {
        if (!_file_path.ends_with(".wav") && !_file_path.ends_with(".mp3"))
            throw std::runtime_error("Unsupported file format");
    }
    ~SoundAsset(void) override = default;

    void load(void) override
    {
        _sound_data = _read_file_binary(_file_path);
    }

private:
    std::vector<std::uint8_t> _sound_data;
};

class AssetFactory
{
public:
    using AssetCreator = std::function<std::shared_ptr<Asset>(std::string name, std::string file_path)>;

    void registerAsset(const std::string &type, AssetCreator creator)
    {
        creators[type] = creator;
    }

    std::shared_ptr<Asset> createAsset(const std::string &type, const std::string &name, const std::string &file_path)
    {
        auto it = creators.find(type);
        if (it != creators.end())
        {
            return it->second(name, file_path);
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, AssetCreator> creators;
};
