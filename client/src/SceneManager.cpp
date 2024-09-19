/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

#include "Engine.hpp"

LE::SceneManager::SceneManager()
{
    _currentScene = nullptr;
    _previousScene = nullptr;
    _currentSceneName = "";
    _previousSceneName = "";
}

LE::SceneManager::~SceneManager()
{
}

void LE::SceneManager::play()
{

    LE::Engine *engineInstance = LE::Engine::getInstance();

    engineInstance->debug("SceneManager::play()");
    if (!_currentScene) {
        engineInstance->debug("SceneManager::play() - No current scene, selecting first scene.");
        engineInstance->debug("SceneManager::play() - Number of scenes: " + std::to_string(_scenes.size()));
        _currentScene = _scenes.begin()->second;
        _currentSceneName = _scenes.begin()->first;
        engineInstance->debug("SceneManager::play() - first scene selected: " + _currentSceneName);
    }
    engineInstance->debug("SceneManager::play() - Playing selected scene");
    _currentScene->play();
}

void LE::SceneManager::play(const std::string &sceneName)
{
    auto it = _scenes.find(sceneName);

    if (it != _scenes.end()) {
        if (_currentScene) {
            _previousScene = _currentScene;
            _previousSceneName = _currentSceneName;
            _currentScene->stop();
        }
        _currentScene = it->second;
        _currentSceneName = sceneName;
        _currentScene->play();
    } else {
        throw SceneManagerError("Scene not found: " + sceneName);
    }
}

void LE::SceneManager::stop()
{
    if (_currentScene) {
        _currentScene->stop();
    } else {
        throw SceneManagerError("No current scene to stop.");
    }
}

std::shared_ptr<LE::Scene> LE::SceneManager::getCurrentScene() const
{
    return _currentScene;
}

std::shared_ptr<LE::Scene> LE::SceneManager::getPreviousScene() const
{
    return _previousScene;
}

void LE::SceneManager::addScene(std::shared_ptr<LE::Scene> scene, const std::string &name)
{
    _scenes[name] = scene;

    std::cout << "Scene name added: " << name << std::endl;
    std::cout << "Scene added: " << scene.get() << std::endl;
    std::cout << "Current scene :" << _currentScene.get() << std::endl;
    if (!_currentScene) {
        _currentScene = scene;
        _currentSceneName = name;
    }
}

void LE::SceneManager::removeScene(const std::string &sceneName)
{
    auto it = _scenes.find(sceneName);
    if (it != _scenes.end()) {
        _scenes.erase(it);
    } else {
        throw SceneManagerError("Scene not found: " + sceneName);
    }
}

void LE::SceneManager::selectScene(const std::string &sceneName)
{
    auto it = _scenes.find(sceneName);
    if (it != _scenes.end()) {
        if (_currentScene) {
            _previousScene = _currentScene;
            _previousSceneName = _currentSceneName;
            _currentScene->stop();
        }
        _currentScene = it->second;
        _currentSceneName = sceneName;
    } else {
        throw SceneManagerError("Scene not found: " + sceneName);
    }
}