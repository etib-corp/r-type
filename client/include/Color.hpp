/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Color
*/

#pragma once

#include "Maths/Vector4.hpp"
#include "Error.hpp"

namespace LE {
    /**
     * @class Color
     * @brief The Color class represents a color in RGBA format.
     *
     * The Color class provides functionalities for creating and managing colors in RGBA format.
     * @note The color values are stored as floats in the range [0, 1], to be compatible with OpenGL.
     */
    class Color final {
        public:
            /**
             * @class ColorError
             * @brief Exception class for color-related errors.
             *
             * This class is used to represent errors that occur within the Color class.
             */
            class ColorError : public Error {
                public:
                    /**
                     * @brief Constructs a ColorError object with the specified error message.
                     *
                     * @param message The error message.
                     */
                    ColorError(const std::string& message) : Error(message) {}
            };

            enum UseMode {
                FLOAT,
                CHAR
            };

            /**
             * @brief Constructs a Color object with default values (red).
             */
            Color();

            /**
             * @brief Constructs a Color object with the specified RGBA values.
             *
             * @param mode The mode to use (CHAR or FLOAT).
             * @param r The red value.
             * @param g The green value.
             * @param b The blue value.
             * @param a The alpha value (default is 1.0).
             */
            Color(UseMode mode, float r, float g, float b, float a = 1.0f);

            /**
             * @brief Constructs a Color object with the specified hex value.
             *
             * @param hex The hex value.
             * @param a The alpha value (default is 1.0).
             */
            Color(unsigned int hex, float a = 1.0f);

            /**
             * @brief Destructor for the Color object.
             */
            ~Color();

            /**
             * @brief Sets the RGBA values of the color.
             *
             * @param mode The mode to use (CHAR or FLOAT).
             * @param r The red value.
             * @param g The green value.
             * @param b The blue value.
             * @param a The alpha value (default is 1.0).
             */
            void set(UseMode mode, float r, float g, float b, float a = 1.0f);

            /**
             * @brief Sets the RGBA values of the color.
             *
             * @param hex The hex value.
             * @param a The alpha value (default is 1.0).
             */
            void set(unsigned int hex, float a = 1.0f);

            /**
             * @brief Gets the RGBA values of the color as a Vector4.
            */
            Vector4<float> toVector4() const;


            /**
             * @brief Gets the red value of the color.
             *
             * @return The red value.
             */
            float _r;

            /**
             * @brief Gets the green value of the color.
             *
             * @return The green value.
             */
            float _g;

            /**
             * @brief Gets the blue value of the color.
             *
             * @return The blue value.
             */
            float _b;

            /**
             * @brief Gets the alpha value of the color.
             *
             * @return The alpha value.
             */
            float _a;
    };
}
