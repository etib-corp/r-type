/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** SpriteComponent
*/

#include "ECS/Components/SpriteComponent.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>

SpriteComponent *createSpriteComponent(std::string path)
{
    SpriteComponent *sprite = new SpriteComponent;
    sprite->path = path;
    glGenTextures(1, &sprite->id);

    sprite->data = stbi_load(path.c_str(), &sprite->width, &sprite->height, &sprite->channels, 0);

    glBindTexture(GL_TEXTURE_2D, sprite->id);
    if (!sprite->data)
        throw std::runtime_error("Failed to load image: " + path);
    std::cout << "channels: " << sprite->channels << std::endl;
    switch (sprite->channels) {
        case 3:
            sprite->internalFormat = GL_RGB;
            sprite->imageFormat = GL_RGB;
            break;
        case 4:
            sprite->internalFormat = GL_RGBA;
            sprite->imageFormat = GL_RGBA;
            break;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, sprite->internalFormat, sprite->width, sprite->height, 0, sprite->imageFormat, GL_UNSIGNED_BYTE, sprite->data);
    stbi_image_free(sprite->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sprite->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sprite->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sprite->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sprite->filterMax);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenVertexArrays(1, &sprite->quadVAO);
    glGenBuffers(1, &sprite->quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, sprite->quadVBO);

    glBindVertexArray(sprite->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return sprite;
}
