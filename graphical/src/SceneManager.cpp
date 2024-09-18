/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

LE::SceneManager::SceneManager()
{
}

LE::SceneManager::~SceneManager()
{
}

void LE::SceneManager::play()
{
    if (_currentScene) {
        _currentScene->play();
    } else {
        throw SceneManagerError("No current scene to play.");
    }
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