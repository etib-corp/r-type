/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Button
*/

#pragma once

#include "GUI/Interactable.hpp"
#include "GUI/Text.hpp"

namespace LE {
    namespace GUI {
        /**
         * @class Button
         * @brief The Button class represents a button in the GUI.
         *
         * The Button class is a subclass of the Interactable class and represents a button in the GUI.
         */
        class Button : public Interactable {
            public:
                /**
                 * @brief Constructs a new Button object.
                 *
                 * This constructor initializes the Button object with the specified position, size, content, background color, and text color.
                 *
                 * @param x The x-coordinate of the button.
                 * @param y The y-coordinate of the button.
                 * @param width The width of the button.
                 * @param height The height of the button.
                 * @param content The content of the button.
                 * @param bgColor The background color of the button.
                 * @param textColor The text color of the button.
                 */
                Button(float x, float y, float width, float height, const std::string &content, Color *bgColor, Color *textColor);

                /**
                 * @brief Destructor for the Button class.
                 */
                ~Button();

                /**
                 * @brief Function to draw the button.
                 *
                 * This function is responsible for rendering the button on the screen.
                 */
                void draw() override;
        };
    }
}
