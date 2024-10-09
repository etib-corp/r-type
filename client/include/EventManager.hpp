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
#include <memory>
#include <string>
#include <map>

/**
 * @file EventManager.hpp
 * @brief Defines the EventManager class and its associated error handling.
 */

namespace LE
{
    /**
     * @struct Status
     * @brief Represents the status of an operation.
     * 
     * The Status struct represents the status of an operation, such as success or failure.
     * It includes the following values:
     * - success: A boolean value indicating whether the operation was successful.
     * - message: A string message providing additional information about the operation.
     */
    typedef struct
    {
        bool success;
        std::string message;
    } Status;

    /**
     * @enum Type
     * @brief Represents the type of an event.
     *
     * The Type enum represents the type of an event, such as a key press or release.
     * It includes the following values:
     * - PRESSED: The key is currently pressed.
     * - RELEASED: The key is currently released.
     * - JUST_PRESSED: The key was just pressed.
     * - JUST_RELEASED: The key was just released.
     */
    typedef enum
    {
        PRESSED,
        RELEASED,
        JUST_PRESSED,
        JUST_RELEASED
    } Type;

    /**
     * @enum Input
     * @brief Represents the input source of an event.
     *
     * The Input enum represents the input source of an event, such as a keyboard or mouse.
     * It includes the following values:
     * - KEYBOARD: The event is from a keyboard.
     * - MOUSE: The event is from a mouse.
     * - JOYSTICK_BUTTON: The event is from a joystick button.
     * - JOYSTICK_AXIS: The event is from a joystick axis.
     */
    typedef enum
    {
        KEYBOARD,
        MOUSE,
        JOYSTICK_BUTTON,
        JOYSTICK_AXIS
    } Input;

    /**
     * @struct Key
     * @brief Represents a key event.
     *
     * The Key struct represents a key event, including the input source, key code, and event type.
     * It includes the following values:
     * - input: The input source of the event.
     * - key: The key code of the event.
     * - type: The type of the event.
     * - _alreadyPressed: A boolean value indicating whether the key was already pressed.
     */
    typedef struct
    {
        Input input;
        int key;
        Type type;
        bool _alreadyPressed;
    } Key;

    /**
     * @class EventManager
     * @brief Manages events within the application.
     *
     * The EventManager class is responsible for managing events within the application,
     * including registering event listeners and polling for events. It maintains a
     * collection of event listeners and dispatches events to the appropriate listeners.
     *
     * @note This class uses the EventManagerError custom exception class to handle
     * errors specific to event management.
     *
     * @see EventManagerError
     */
    class EventManager
    {
    public:
        /**
         * @class EventManagerError
         * @brief A custom exception class for handling errors specific to the EventManager.
         *
         * This class inherits from the base Error class and is used to represent
         * errors that occur within the EventManager. It provides a constructor
         * that accepts an error message.
         *
         * @see Error
         */
        class EventManagerError : public Error
        {
        public:
            /**
             * @brief Constructs a new EventManagerError object.
             *
             * @param message The error message to be associated with this exception.
             */
            EventManagerError(const std::string &message) : Error(message) {}
        };
        /**
         * @brief Constructs a new EventManager object.
         */
        EventManager();

        /**
         * @brief Destructor for the EventManager class.
         */
        ~EventManager();

        /**
         * @brief Adds an event listener for the specified key.
         *
         * This method adds an event listener for the specified key, which will be called
         * whenever the key event occurs. The callback function will be passed a pointer
         * to the Engine object.
         *
         * @param key The key to listen for.
         * @param callback The callback function to be called when the key event occurs.
         * @return A Status object indicating the success or failure of the operation.
         */
        Status addEventListener(const LE::Key &key, std::function<void(LE::Engine *)> callback);

        /**
         * @brief Removes an event listener for the specified key.
         *
         * This method removes an event listener for the specified key, which will no longer
         * be called when the key event occurs.
         *
         * @param key The key to remove the event listener for.
         * @param callback The callback function to be removed.
         */
        void removeEventListener(const LE::Key &key, std::function<void(LE::Engine *)> callback);

        /**
         * @brief Polls for events and dispatches them to the appropriate listeners.
         */
        void pollEvents();

    private:
        std::map<std::shared_ptr<LE::Key>, std::function<void(LE::Engine *engine)>> _eventCallbacks; ///< List of event callbacks.
    };
}
