/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Triangle
*/

#pragma once

#include "Shapes/Shape.hpp"

namespace LE {
    class Engine;
}

namespace LE {
    namespace Shapes {
        /**
         * @class Triangle
         * @brief The Triangle class is responsible for managing OpenGL triangles.
         *
         * The Triangle class provides functionalities for drawing and moving OpenGL triangles.
         */
        class Triangle final : public Shape {
            public:
                /**
                 * @brief Construct a new Triangle object
                 *
                 * @param p1 The first point of the triangle
                 * @param p2 The second point of the triangle
                 * @param p3 The third point of the triangle
                 */
                Triangle(Vector3<float> p1, Vector3<float> p2, Vector3<float> p3);

                /**
                 * @brief Destroy the Triangle object
                 */
                ~Triangle();

                /**
                 * @brief Move the triangle by the given offset
                 *
                 * @param offset The offset to move the triangle by
                 */
                void move(Vector3<float> offset);

                /**
                 * @brief Draw the triangle
                 */
                void draw();

                /**
                 * @brief Initialize the triangle
                 */
                void init();

            private:
                Vector3<float> _p1; // The first point of the triangle
                Vector3<float> _p2; // The second point of the triangle
                Vector3<float> _p3; // The third point of the triangle
                GLuint _VAO; // The vertex array object where the triangle is stored
                GLuint _VBO; // The vertex buffer object where the triangle is stored
        };
    }
}
