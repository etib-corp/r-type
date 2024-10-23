/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TextField
*/

#pragma once

#include "GUI/Interactable.hpp"
#include "GUI/Text.hpp"

namespace LE {
    namespace GUI {
        class TextField : public Interactable {
            public:
                /**
                 * @brief Construct a new TextField object
                 *
                 * The TextField is composed of:
                 * - A label
                 * - A content
                 *
                 * The Content is editable and can be focused by clicking on it. The TextField width is automatically resized to the largest child width (label or content).
                 *
                 * @param x The x position of the text field
                 * @param y The y position of the text field
                 * @param width The width of the text field
                 * @param height The height of the text field
                 * @param label The label of the text field
                 * @param bgColor The background color of the text field
                 * @param textColor The text color of the text field
                 */
                TextField(float x, float y, float width, float height, const std::string &label, LE::Color *bgColor, LE::Color *textColor, const std::string &placeholder = "Message");

                /**
                 * @brief Destroy the TextField object
                 */
                ~TextField();

                /**
                 * @brief Set the max chars of the text field.
                 * (default: 18)
                 *
                 * @param maxChars The max chars of the text field
                 */
                void setMaxChars(unsigned int maxChars);

                /**
                 * @brief Draw the text field
                 *
                 * Inherited from the Component class
                 */
                void draw() override;

                /**
                 * @brief Initialize the text field
                 *
                 * Inherited from the Component class
                 */
                void init() override;

                /**
                 * @brief Function called when the text field is clicked.
                 *
                 * Inherited from the Interactable class
                 *
                 * Override this function to add custom behavior when the text field is clicked
                 */
                void OnClick() override;

                /**
                 * @brief Function called when the text field is hovered.
                 *
                 * Inherited from the Interactable class
                 *
                 * Override this function to add custom behavior when the text field is hovered
                 */
                void OnHover() override;

                /**
                 * @brief Function called when the text field is unhovered.
                 *
                 * Inherited from the Interactable class.
                 *
                 * Override this function to add custom behavior when the text field is unhovered
                 */
                void OnUnhover() override;

                std::string getContent();

                std::shared_ptr<LE::GUI::Text> getText();

            protected:
                std::string _placeholder;           // The placeholder of the text field
                std::shared_ptr<LE::GUI::Text> _label;          // The label of the text field (short description of the content)
                std::shared_ptr<LE::GUI::Text> _content;        // The content of the text field
                bool _focused;                  // The focus state of the text field
                unsigned int _maxChars = 18;    // The max chars of the text field (default: 18)
        };
    }
}
