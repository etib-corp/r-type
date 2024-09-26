/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Font
*/

#include "GUI/Font.hpp"

LE::GUI::Font::Font(unsigned int height, const std::string &fontPath, unsigned int width)
{
    _height = height;
    _fontPath = fontPath;
    _width = width;
}

LE::GUI::Font::~Font()
{
}

void LE::GUI::Font::init()
{
    fontShader->use();
    if (FT_Init_FreeType(&_library)) {
        throw FontError("Failed to initialize FreeType library.");
    }

    if (FT_New_Face(_library, _fontPath.c_str(), 0, &_face)) {
        throw FontError("Failed to load " + _fontPath + " font.");
    }

    FT_Set_Pixel_Sizes(_face, _width, _height);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c < 128; c++) {
        unsigned int texture;

        if (FT_Load_Char(_face, c, FT_LOAD_RENDER)) {
            throw FontError("Failed to load Glyph for character " + c);
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            _face->glyph->bitmap.width,
            _face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            _face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
            glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
            static_cast<unsigned int>(_face->glyph->advance.x)
        };
        _characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(_face);
    FT_Done_FreeType(_library);
    _initialized = true;
}