/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Text
*/

#pragma once

#include "Shader.hpp"
#include "GUI/Component.hpp"
#include "GUI/Font.hpp"

namespace LE {
    namespace Shapes {
        class Triangle;
    }
}

namespace LE {
    namespace GUI {
        /**
         * @class Text
         * @brief The Text class is responsible for managing text in the graphical system.
         *
         * The Text class provides functionalities for loading and rendering text in the graphical system.
         */
        class Text final : public Component {
            public:
                /**
                 * @brief Constructs a new Text object (GUI).
                 *
                 * This constructor initializes the Text object with the specified ID, font path, font height, and content.
                 *
                 * @param id The ID of the text.
                 * @param fontPath The path to the font file.
                 * @param fontHeight The height of the font.
                 * @param content The content of the text. (Default: "Hello World !")
                 * @param fontWidth The width of the font. (Default: 0)
                 *
                 * @note The `fontHeight` and `fontWidth` parameters are in pixels (`px`) and represent the size of the font.
                 */
                Text(unsigned int id, const std::string &fontPath, unsigned int fontHeight, const std::string &content = "Hello World !", unsigned int fontWidth = 0);

                /**
                 * @brief Destructor for the Text object.
                 */
                ~Text();

                /**
                 * @brief Function to draw the text.
                 *
                 * This function is responsible for rendering the text on the screen.
                 */
                void draw() override;

                /**
                 * @brief Function to initialize the text.
                 *
                 * This function is responsible for initializing the text before engine rendering.
                 */
                void init() override;

            protected:
                std::string _content; /** The text content. */
                LE::GUI::Font *_font;  /** The text font. */
                GLuint _VAO;       /** Vertex Array Object where the Text is drawn. */
                GLuint _VBO;       /** Vertex Buffer Object where the Text is stored. */
        };
    }
}
