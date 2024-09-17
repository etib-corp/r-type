/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <string>

#include "Scene.hpp"
#include "Error.hpp"

namespace LE {
    class SceneManagerError : public Error {
        public:
            SceneManagerError(const std::string &message) : Error(message) {}
    };

    class SceneManager {
        public:
            SceneManager();
            ~SceneManager();

            void play();
            void play(const std::string &sceneName);
            void stop();

        private:
            std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes;
            std::string _currentSceneName;
            std::shared_ptr<Scene> _currentScene;
            std::string _previousSceneName;
            std::shared_ptr<Scene> _previousScene;
    };
}

#endif /* !SCENEMANAGER_HPP_ */
