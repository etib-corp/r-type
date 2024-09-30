/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Font
*/

#pragma once

#include <map>
#include "ft2build.h"

#include "glm.hpp"

#include "Window.hpp"
#include "Shader.hpp"

#include "Error.hpp"

#include FT_FREETYPE_H

namespace LE {
    namespace GUI {
        /**
         * @class Font
         * @brief The Font class is responsible for managing fonts in the graphical system.
         *
         * The Font class provides functionalities for loading and rendering fonts in the graphical system.
         */
        class Font final {
            public:
                /**
                 * @class FontError
                 * @brief Exception class for font-related errors.
                 *
                 * This class is used to represent errors that occur within the Font class.
                 */
                class FontError : public Error {
                    public:
                        /**
                         * @brief Constructor for FontError.
                         * @param message The error message.
                         */
                        FontError(const std::string &message) : Error(message) {}
                };

                /**
                 * @brief Constructs a new Font object.
                 *
                 * This constructor initializes the Font object with the specified height and font path.
                 *
                 * @param height The height of the font.
                 * @param fontPath The path to the font file.
                 * @param width The width of the font.
                 */
                Font(unsigned int height, const std::string &fontPath, unsigned int width = 0);

                /**
                 * @brief Destructor for the Font object.
                 */
                ~Font();

                /**
                 * @brief Character representation for the font.
                 *
                 * This struct represents a character in the font, including the texture ID, size, bearing, and advance.
                 */
                struct Character {
                    unsigned int TextureID; // ID handle of the glyph texture
                    glm::ivec2   Size;     // Size of glyph
                    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
                    unsigned int Advance;   // Offset to advance to next glyph
                };

                /**
                 * @brief Loads the font.
                 *
                 * This function loads the font from the specified font file.
                 *
                 * @note This function must be called before rendering text with the font. But it has to be called right after the window is created.
                 */
                void init();

                std::map<char, Character> _characters;  // Holds a list of characters
                Shader *_shader;                        // Shader used to render the font
                bool _initialized = false;              // Flag indicating whether the font has been initialized
            private:
                FT_Library _library;    // FreeType library (OpenGL level)
                FT_Face _face;          // FreeType face (OpenGL level)
                unsigned int _height;   // Height of the font
                unsigned int _width = 0; // Width of the font
                std::string _fontPath;  // Path to the font file

        };
    }
}
