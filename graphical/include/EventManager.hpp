/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** EventManager
*/

#pragma once

namespace LE {
    class Engine;
}
#include "Error.hpp"
#include "Keys.hpp"

#include <functional>
#include "GLFW/glfw3.h"
#include <memory>
#include <string>
#include <map>

using Status = struct {
    bool success;
    std::string message;
};

using Type = enum {
    PRESSED,
    RELEASED,
    JUST_PRESSED,
    JUST_RELEASED
};

using Input = enum {
    KEYBOARD,
    MOUSE,
    JOYSTICK_BUTTON,
    JOYSTICK_AXIS
};

typedef struct {
    int key;
    bool _alreadyPressed;
    Type type;
    Input input;
} Key;



namespace LE {
    class EventManager {
        public:
            class EventManagerError : public Error {
                public:
                    EventManagerError(const std::string &message) : Error(message) {}
            };
            EventManager();
            ~EventManager();

            Status addEventListener(Key key, std::function<void(LE::Engine *)> callback);
            void removeEventListener(Key key, std::function<void(LE::Engine *)> callback);

            void pollEvents();

        private:
            std::map<std::shared_ptr<Key>, std::function<void(LE::Engine *engine)>> _eventCallbacks;     ///< List of event callbacks.
    };
}