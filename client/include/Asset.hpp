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
    Asset(std::string name) : _name(name) {}

    /**
     * @brief Destructor for the Asset class.
     */
    virtual ~Asset(void) = default;

    /**
     * @brief Gets the name of the asset.
     * @return The name of the asset.
     */
    std::string getName(void) const { return _name; }

    /**
     * @brief Loads the asset.
     */
    virtual void load(void) = 0;

protected:
    std::string _name;

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
    ConfigAsset(std::string name, std::string file_path) : Asset(name)
    {
        _config_file = file_path;

        if (!_config_file.ends_with(".json"))
            throw std::runtime_error("Unsupported file format");
    }
    ~ConfigAsset(void) override = default;

    void load(void) override
    {
        std::cout << "Loading file: " << _config_file << std::endl;
        _config_data = _read_file(_config_file);
    }

    std::string getConfigFile(void) const { return _config_file; }

    std::string getConfigData(void) const { return _config_data; }

private:
    std::string _config_file;
    std::string _config_data;
};

class FontAsset : public Asset
{
public:
    FontAsset(std::string name, std::string file_path) : Asset(name)
    {
        _font_file = file_path;

        if (!_font_file.ends_with(".ttf"))
            throw std::runtime_error("Unsupported file format");
    }
    ~FontAsset(void) override = default;

    void load(void) override
    {
        std::cout << "Loading file: " << _font_file << std::endl;
        _font_data = _read_file_binary(_font_file);
    }

    std::string getFontFile(void) const { return _font_file; }

    std::vector<std::uint8_t> getFontData(void) const { return _font_data; }

private:
    std::string _font_file;
    std::vector<std::uint8_t> _font_data;
};

class ImageAsset : public Asset
{
public:
    ImageAsset(std::string name, std::string file_path) : Asset(name)
    {
        _image_file = file_path;

        if (!_image_file.ends_with(".png"))
            throw std::runtime_error("Unsupported file format");
    }
    ~ImageAsset(void) override = default;

    void load(void) override
    {
        std::cout << "Loading file: " << _image_file << std::endl;
        _image_data = _read_file_binary(_image_file);
    }

    std::string getImageFile(void) const { return _image_file; }

    std::vector<std::uint8_t> getImageData(void) const { return _image_data; }

private:
    std::string _image_file;
    std::vector<std::uint8_t> _image_data;
};

class ModelAsset : public Asset
{
public:
    ModelAsset(std::string name, std::string file_path) : Asset(name)
    {
        _model_file = _get_material_file_path(file_path);
        _material_file = _get_material_file_path(file_path);

        if (!std::filesystem::exists(_model_file))
            throw std::runtime_error("Model file: " + _model_file + " not found");

        if (!std::filesystem::exists(_material_file))
            throw std::runtime_error("Material file: " + _material_file + " not found");
    }
    ~ModelAsset(void) override = default;

    void load(void) override
    {
        std::cout << "Loading file: " << _model_file << std::endl;
        std::cout << "Loading file: " << _material_file << std::endl;

        _model_data = _read_file(_model_file);
        _material_data = _read_file(_material_file);
    }

    std::string getModelFile(void) const { return _model_file; }

    std::string getMaterialFile(void) const { return _material_file; }

    std::string getModelData(void) const { return _model_data; }

    std::string getMaterialData(void) const { return _material_data; }

private:
    std::string _model_file;
    std::string _material_file;
    std::string _model_data;
    std::string _material_data;

    std::string _get_model_file_path(std::string file_path) {
        return file_path + "/" + _name + ".obj";
    }

    std::string _get_material_file_path(std::string file_path) {
        return file_path + "/" + _name + ".mtl";
    }
};

class ShaderAsset : public Asset
{
public:
    ShaderAsset(std::string name, std::string file_path) : Asset(name)
    {
        _fragment_file = _get_fragment_file_path(file_path);
        _vertice_file = _get_vertice_file_path(file_path);

        if (!std::filesystem::exists(_fragment_file))
            throw std::runtime_error("Fragment file: " + _fragment_file + " not found");

        if (!std::filesystem::exists(_vertice_file))
            throw std::runtime_error("Vertice file: " + _vertice_file + " not found");
    }
    ~ShaderAsset(void) override = default;

    void load(void) override
    {
        std::cout << "Loading file: " << _fragment_file << std::endl;
        std::cout << "Loading file: " << _vertice_file << std::endl;

        _fragment_data = _read_file(_fragment_file);
        _vertice_data = _read_file(_vertice_file);
    }

    std::string getFragmentFile(void) const { return _fragment_file; }

    std::string getVerticeFile(void) const { return _vertice_file; }

    std::string getFragmentData(void) const { return _fragment_data; }

    std::string getVerticeData(void) const { return _vertice_data; }

private:
    std::string _fragment_file;
    std::string _vertice_file;
    std::string _fragment_data;
    std::string _vertice_data;

    std::string _get_fragment_file_path(std::string file_path) {
        return file_path + "/" + _name + ".frag";
    }

    std::string _get_vertice_file_path(std::string file_path) {
        return file_path + "/" + _name + ".vert";
    }
};

class SoundAsset : public Asset
{
public:
    SoundAsset(std::string name, std::string file_path) : Asset(name)
    {
        _sound_file = file_path;

        if (!_sound_file.ends_with(".wav") && !_sound_file.ends_with(".mp3"))
            throw std::runtime_error("Unsupported file format");
    }
    ~SoundAsset(void) override = default;

    void load(void) override
    {
        std::cout << "Loading file: " << _sound_file << std::endl;

        _sound_data = _read_file_binary(_sound_file);
    }

    std::string getSoundFile(void) const { return _sound_file; }

    std::vector<std::uint8_t> getSoundData(void) const { return _sound_data; }

private:
    std::string _sound_file;
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
