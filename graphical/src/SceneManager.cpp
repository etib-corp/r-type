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
    if (this->_currentScene) {
        this->_currentScene->play();
    } else {
        throw SceneManagerError("No current scene to play.");
    }
}

void LE::SceneManager::play(const std::string &sceneName)
{
    auto it = this->_scenes.find(sceneName);

    if (it != this->_scenes.end()) {
        if (this->_currentScene) {
            _previousScene = this->_currentScene;
            _previousSceneName = this->_currentSceneName;
            this->_currentScene->stop();
        }
        this->_currentScene = it->second;
        this->_currentSceneName = sceneName;
        this->_currentScene->play();
    } else {
        throw SceneManagerError("Scene not found: " + sceneName);
    }
}

void LE::SceneManager::stop()
{
    if (this->_currentScene) {
        this->_currentScene->stop();
    } else {
        throw SceneManagerError("No current scene to stop.");
    }
}
