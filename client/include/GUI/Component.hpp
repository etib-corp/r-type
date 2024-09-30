/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Component
*/

#pragma once

#include <string>

namespace LE {
    namespace GUI {
        /**
         * @class Component
         * @brief Abstract base class representing a GUI component.
         *
         * The Component class provides an interface for managing GUI components,
         * including drawing and initialization. It also includes error handling specific
         * to GUI components.
         */
        class Component {
            public:
                virtual ~Component() = default;

                /**
                 * @brief Pure virtual function to draw the component.
                 *
                 * This function is responsible for rendering the component on the screen.
                 *
                 * @note This function is pure virtual and must be implemented by derived classes.
                 */
                virtual void draw() = 0;

                /**
                 * @brief Function that returns the component's ID.
                 *
                 * This function returns the ID of the component.
                 *
                 * @return The component's ID.
                 */
                size_t getId() const { return _id; }

                /**
                 * @brief Virtual function to initialize the component.
                 *
                 * This function is responsible for initializing the component before engine rendering.
                 *
                 * @note This function is pure virtual and must be implemented by derived classes.
                 */
                virtual void init() = 0;

                /**
                 * @brief Function to set the component's position.
                 *
                 * This function sets the X and Y position of the component on the screen.
                 *
                 * @param x The X position of the component.
                 * @param y The Y position of the component.
                 */
                void setPos(float x, float y) { _x = x; _y = y; }

                /**
                 * @brief Function to set the component's width.
                 *
                 * This function sets the width of the component.
                 *
                 * @param width The width of the component.
                 */
                float getWidth() const { return _width; }

                /**
                 * @brief Function to set the component's height.
                 *
                 * This function sets the height of the component.
                 *
                 * @param height The height of the component.
                 */
                float getHeight() const { return _height; }

            protected:
                size_t _id; /** The component's ID. @note Unique for each component. */
                float _x; /**< The component's X position on the screen. */
                float _y; /**< The component's Y position on the screen. */
                float _width; /**< The component's width. */
                float _height; /**< The component's height. */
        };
    }
}
