/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Interactable
*/

#pragma once

#include "Engine.hpp"

#include "GUI/Container.hpp"

namespace LE {
    namespace GUI {
        /**
         * @brief Interface for interactable GUI objects
         */
        class Interactable : public Container {
            public:
                /**
                 * @brief Destructor for the Interactable class.
                 */
                virtual ~Interactable() = default;

                /**
                 * @brief Function called when the object is clicked.
                 */
                virtual void OnClick() = 0;

                /**
                 * @brief Function called when the object is hovered.
                 */
                virtual void OnHover() = 0;

                /**
                 * @brief Function called when the object is unhovered.
                 */
                virtual void OnUnhover() = 0;

                /**
                 * @brief Function to check if the object is hovered.
                 *
                 * @return true if the object is hovered, false otherwise.
                 */
                [[nodiscard]] bool isHover();
        };
    }
}
