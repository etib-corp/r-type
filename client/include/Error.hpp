/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Error
*/

#pragma once

// C++ include
#include <exception>
#include <string>

namespace LE {
    /**
     * @brief The Error class represents an exception that can be thrown in the Lion engine.
     *
     * This class inherits from std::exception and provides a custom error message.
     */
    class Error : public std::exception {
    public:
        /**
         * @brief Constructs an Error object with the specified error message.
         *
         * @param message The error message.
         */
        Error(const std::string& message) : _message(message) {}

        /**
         * @brief Destructor for the Error object.
         */
        ~Error() {}

        /**
         * @brief Returns a C-style string representing the error message.
         *
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept override { return _message.c_str(); }
    protected:
        std::string _message; /**< The error message. */
    };
}