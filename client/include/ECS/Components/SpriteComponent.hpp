/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SpriteComponent
*/

#pragma once

#include "Maths/Vector4.hpp"
#include "Window.hpp"

/**
 * @brief A sprite component.
 *
 * This component represents a sprite with a path, width, height, channels, id, internal format, image format, wrap S, wrap T, filter min, filter max, quad VAO, quad VBO, data and rect.
 */
struct SpriteComponent {
    std::string path;                       ///< The path of the sprite.
    int width = 0;                          ///< The width of the sprite.
    int height = 0;                         ///< The height of the sprite.
    int channels = 0;                       ///< The channels of the sprite.
    unsigned int id = 0;                    ///< The id of the sprite.
    unsigned int internalFormat = GL_RGB;   ///< The internal format of the sprite.
    unsigned int imageFormat = GL_RGB;      ///< The image format of the sprite.
    unsigned int wrapS = GL_REPEAT;         ///< The wrap S of the sprite.
    unsigned int wrapT  = GL_REPEAT;        ///< The wrap T of the sprite.
    unsigned int filterMin = GL_LINEAR;     ///< The filter min of the sprite.
    unsigned int filterMax = GL_LINEAR;     ///< The filter max of the sprite.
    unsigned int quadVAO = 0;               ///< The quad VAO of the sprite.
    unsigned int quadVBO = 0;               ///< The quad VBO of the sprite.
    unsigned char *data = nullptr;          ///< The data of the sprite.
    LE::Vector4<float> rect = {0.0f, 0.0f, 1.0f, 1.0f};     ///< The rect of the sprite.
};

/**
 * @brief Creates a sprite component with the specified path.
 *
 * @param path The path of the sprite.
 * @return The sprite component.
 */
SpriteComponent *createSpriteComponent(std::string path);