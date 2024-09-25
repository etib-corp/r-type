/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Container
*/

#pragma once

#include <vector>

#include "GUI/Component.hpp"

namespace LE {
    namespace GUI {
        /**
         * @class Container
         * @brief Abstract base class representing a GUI container.
         *
         * The Container class provides an interface for managing GUI containers,
         * including adding and removing children components. It also includes error handling specific
         * to GUI containers.
         */
        class Container : public Component {
            public:
                /**
                 * @brief Constructs a new Container object.
                 *
                 * This constructor initializes the Container, setting up any necessary
                 * resources or configurations required for managing GUI containers within the application.
                 */
                virtual ~Container() = default;

                /**
                 * @brief Function to add a child component to the container.
                 *
                 * This function adds a child component to the container.
                 *
                 * @param child The child component to add.
                 */
                void addChildren(Component *child);

                /**
                 * @brief Function to remove a child component from the container.
                 *
                 * This function removes a child component from the container.
                 *
                 * @param id The ID of the child component to remove.
                 */
                void removeChildren(unsigned int id);

                /**
                 * @brief Function to draw the container.
                 *
                 * This function is responsible for rendering the container on the screen.
                 */
                void draw();

            protected:
                std::vector<Component *> _children; /**< The container's children components. @note Similar to React components. */
                unsigned int _width; /**< The container's width (In pixels`px`) */
                unsigned int _height; /**< The container's height (In pixels`px`) */
        };
    }
}
