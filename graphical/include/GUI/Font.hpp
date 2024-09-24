/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Font
*/

#pragma once

#include <map>
#include <ft2build.h>

#include "glm.hpp"

#include "Window.hpp"
#include "Shader.hpp"

#include "Error.hpp"
#include FT_FREETYPE_H

namespace LE {
    namespace GUI {
        class Font final {
            public:
                class FontError : public Error {
                    public:
                        /**
                         * @brief Constructor for FontError.
                         * @param message The error message.
                         */
                        FontError(const std::string &message) : Error(message) {}
                };

                Font(unsigned int height, const std::string &fontPath, unsigned int width = 0);
                ~Font();

                struct Character {
                    unsigned int TextureID;
                    glm::ivec2   Size;
                    glm::ivec2   Bearing;
                    unsigned int Advance;
                };

                void init();

                std::map<char, Character> _characters;
                Shader *_shader;
                bool _initialized = false;
            private:
                FT_Library _library;
                FT_Face _face;
                unsigned int _height;
                unsigned int _width = 0;
                std::string _fontPath;

        };
    }
}
