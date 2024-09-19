/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** EventManager
*/

#include "EventManager.hpp"
#include "Engine.hpp"
#include "Window.hpp"

LE::EventManager::EventManager()
{
}

LE::EventManager::~EventManager()
{
}

LE::Status LE::EventManager::addEventListener(const LE::Key& key, std::function<void(LE::Engine *)> callback)
{
    auto newKey = std::make_shared<Key>(key);
    auto it = _eventCallbacks.find(newKey);
    if (it != _eventCallbacks.end()) {
        return {false, "Event listener already exists for this event type."};
    }
    _eventCallbacks[newKey] = callback;
    return {true, "Event listener added successfully."};
}

void LE::EventManager::removeEventListener(const LE::Key& key, std::function<void(LE::Engine *)> callback)
{
    auto it = _eventCallbacks.find(std::make_shared<Key>(key));
    if (it != _eventCallbacks.end() && it->second.target<void(LE::Engine *)>() == callback.target<void(LE::Engine *)>()) {
        _eventCallbacks.erase(it);
    }
}

void LE::EventManager::pollEvents()
{
    // TODO manage multiple joysticks
    glfwPollEvents();
    int keyCurrentState = -1;
    static int joystickCount = 0;
    static const float *axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &joystickCount);
    static int buttonCount = 0;
    static const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    for (auto& [key, callback] : _eventCallbacks) {
        if (key->input == Input::KEYBOARD) {
            keyCurrentState = glfwGetKey(LE::Engine::getInstance()->_window->getWindow(), key->key);
        } else if (key->input == Input::MOUSE) {
            keyCurrentState = glfwGetMouseButton(LE::Engine::getInstance()->_window->getWindow(), key->key);
        } else if (key->input == Input::JOYSTICK_BUTTON) {
            if (key->key < 0 || key->key >= buttonCount) {
                LE::Engine::getInstance()->throwError(LE::EventManager::EventManagerError("Invalid joystick button. Got " + std::to_string(key->key)));
            }
            keyCurrentState = buttons[key->key];
        } else if (key->input == Input::JOYSTICK_AXIS) {
            keyCurrentState = axis[key->key];
        } else {
            LE::Engine::getInstance()->throwError(LE::EventManager::EventManagerError("Invalid input type. Got " + std::to_string(key->input)));
        }
        if (keyCurrentState == GLFW_PRESS && key->type == Type::PRESSED) {
            callback(LE::Engine::getInstance());
        } else if (keyCurrentState == GLFW_RELEASE && key->type == Type::RELEASED) {
            callback(LE::Engine::getInstance());
        } else if (keyCurrentState == GLFW_PRESS && key->type == Type::JUST_PRESSED && !key->_alreadyPressed) {
            callback(LE::Engine::getInstance());
        } else if (keyCurrentState == GLFW_RELEASE && key->type == Type::JUST_RELEASED && key->_alreadyPressed) {
            callback(LE::Engine::getInstance());
        } else {
        }
        if (keyCurrentState == GLFW_RELEASE) {
            const_cast<std::shared_ptr<Key>&>(key)->_alreadyPressed = false;
        } else if (keyCurrentState == GLFW_PRESS) {
            const_cast<std::shared_ptr<Key>&>(key)->_alreadyPressed = true;
        }
        keyCurrentState = -1;
    }
}