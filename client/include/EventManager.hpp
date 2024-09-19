/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** EventManager
*/

#pragma once

namespace LE
{
    class Engine;
}
#include "Error.hpp"
#include "Keys.hpp"

#include <functional>
#include "GLFW/glfw3.h"
#include <memory>
#include <string>
#include <map>

namespace LE
{
    typedef struct
    {
        bool success;
        std::string message;
    } Status;

    typedef enum
    {
        PRESSED,
        RELEASED,
        JUST_PRESSED,
        JUST_RELEASED
    } Type;

    typedef enum
    {
        KEYBOARD,
        MOUSE,
        JOYSTICK_BUTTON,
        JOYSTICK_AXIS
    } Input;

    typedef struct
    {
        Input input;
        int key;
        Type type;
        bool _alreadyPressed = false;
    } Key;
    class EventManager
    {
    public:
        class EventManagerError : public Error
        {
        public:
            EventManagerError(const std::string &message) : Error(message) {}
        };
        EventManager();
        ~EventManager();

        Status addEventListener(const LE::Key &key, std::function<void(LE::Engine *)> callback);
        void removeEventListener(const LE::Key &key, std::function<void(LE::Engine *)> callback);

        void pollEvents();

    private:
        std::map<std::shared_ptr<LE::Key>, std::function<void(LE::Engine *engine)>> _eventCallbacks; ///< List of event callbacks.
    };
}