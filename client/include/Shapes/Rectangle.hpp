/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rectangle
*/

#pragma once

#include "Shapes/Triangle.hpp"

namespace LE {
    namespace Shapes {
        /**
         * @class Rectangle
         * @brief The Rectangle class is responsible for managing OpenGL rectangles.
         *
         * The Rectangle class provides functionalities for drawing and moving OpenGL rectangles.
         */
        class Rectangle final : public Shape {
            public:
                /**
                 * @brief Construct a new Rectangle object
                 *
                 * @param width The width of the rectangle
                 * @param height The height of the rectangle
                 * @param x The x position of the rectangle
                 * @param y The y position of the rectangle
                 */
                Rectangle(float width, float height, float x, float y, Color *color = nullptr);

                /**
                 * @brief Destroy the Rectangle object
                 */
                ~Rectangle();

                /**
                 * @brief Move the rectangle by the given offset
                 *
                 * @param offset The offset to move the rectangle by
                 */
                void move(Vector3<float> offset);

                /**
                 * @brief Draw the rectangle
                 */
                void draw();

                /**
                 * @brief Initialize the rectangle
                 */
                void init();

                void resize(float width, float height);

            private:
                Triangle *_topLeft; // The top left triangle of the rectangle
                Triangle *_bottomRight; // The bottom right triangle of the rectangle
                float _height;  // The height of the rectangle
                float _width;   // The width of the rectangle
        };
    }
}
