/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Shape
*/

#pragma once

#include "Shader.hpp"

namespace LE {
    namespace Shapes {
        /**
         * @class Shape
         * @brief The Shape class is an abstract base class for managing OpenGL shapes.
         *
         * The Shape class provides an interface for managing OpenGL shapes, including drawing and moving shapes.
         */
        class Shape {
            public:
                virtual ~Shape() = default;

                /**
                 * @brief Draw the shape
                 */
                virtual void draw() = 0;

                /**
                 * @brief Move the shape by the given offset
                 *
                 * @param offset The offset to move the shape by
                 */
                virtual void move(Vector3<float> offset) = 0;

                /**
                 * @brief Initialize the shape
                 */
                virtual void init() = 0;

                virtual void resize(float width, float height) = 0;

                Color *_color; // The color of the shape
        };
    }
}
