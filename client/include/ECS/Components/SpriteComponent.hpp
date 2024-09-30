/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SpriteComponent
*/

#pragma once

#include "Maths/Vector4.hpp"
#include "Window.hpp"

struct SpriteComponent {
    std::string path;
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned int id = 0;
    unsigned int internalFormat = GL_RGB;
    unsigned int imageFormat = GL_RGB;
    unsigned int wrapS = GL_REPEAT;
    unsigned int wrapT  = GL_REPEAT;
    unsigned int filterMin = GL_LINEAR;
    unsigned int filterMax = GL_LINEAR;
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    unsigned char *data = nullptr;
    LE::Vector4<float> rect = {0.0f, 0.0f, 1.0f, 1.0f};
};

SpriteComponent *createSpriteComponent(std::string path);