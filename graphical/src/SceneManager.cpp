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
    if (!_currentScene) {
        _currentScene = _scenes.begin()->second;
        _currentSceneName = _scenes.begin()->first;
    }
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

void LE::SceneManager::init()
{
    for (auto& scene : _scenes) {
        scene.second->init();
    }
}