/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Manager
*/

#pragma once

#include <vector>

#include "GUI/Container.hpp"

namespace LE {
    namespace GUI {
        /**
         * @class Manager
         * @brief The Manager class is responsible for managing GUI components in the graphical system.
         *
         * The Manager class provides functionalities for managing GUI components in the graphical system.
         */
        class Manager final : public Container {
            public:
                /**
                 * @brief Constructs a new Manager object.
                 *
                 * This constructor initializes the Manager object with the specified width and height.
                 *
                 * @note The `height` and `width` parameters are in pixels (`px`) and represent the size of the screen.
                 *
                 * @param width The width of the manager.
                 * @param height The height of the manager.
                 */
                Manager(unsigned int width, unsigned int height);

                /**
                 * @brief Destructor for the Manager object.
                 */
                ~Manager();

                /**
                 * @brief Function to draw the manager.
                 *
                 * This function is responsible for rendering the manager on the screen.
                 */
                void init();
        };
    }
}
