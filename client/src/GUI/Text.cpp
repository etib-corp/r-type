/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Text
*/

#include "GUI/Text.hpp"

#include "Engine.hpp"

LE::GUI::Text::Text(unsigned int id, const std::string &fontPath, unsigned int fontHeight, const std::string &content, unsigned int fontWidth )
{
    _id = id;
    _content = content;
    _font = new LE::GUI::Font(fontHeight, fontPath, fontWidth);
    _x = 0;
    _y = 0;
}

LE::GUI::Text::~Text()
{
}

void LE::GUI::Text::init()
{
    if (!_font->_initialized) {
        _font->init();
    }
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::string::const_iterator c;
    float x = _x;
    float xpos = 0;
    float ypos = 0;
    for (c = _content.begin(); c != _content.end(); c++) {
        LE::GUI::Font::Character ch = _font->_characters[*c];

        xpos = x + ch.Bearing.x;
        ypos = _y - (ch.Size.y - ch.Bearing.y);
        x += (ch.Advance >> 6);
    }
    _width = xpos - _x;
    _height = ypos - _y;
    
}

void LE::GUI::Text::draw()
{
    auto width = Engine::getInstance()->_window->_width;
    auto height = Engine::getInstance()->_window->_height;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    glUniformMatrix4fv(glGetUniformLocation(triangleShader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    fontShader->use();
    glUniform3f(glGetUniformLocation(fontShader->getID(), "textColor"), 1.0, 1.0, 1.0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_VAO);

    std::string::const_iterator c;
    float x = _x;
    float xpos = 0;
    float ypos = 0;
    for (c = _content.begin(); c != _content.end(); c++) {
        LE::GUI::Font::Character ch = _font->_characters[*c];

        xpos = x + ch.Bearing.x;
        ypos = _y - (ch.Size.y - ch.Bearing.y);

        float w = ch.Size.x;
        float h = ch.Size.y;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6);
    }
    _width = xpos - _x;
    _height = ypos - _y;
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}