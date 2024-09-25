/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Manager
*/

#include "GUI/Manager.hpp"

LE::GUI::Manager::Manager(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    _x = 0;
    _y = 0;
}

LE::GUI::Manager::~Manager()
{
}

void LE::GUI::Manager::init()
{
    for (auto &child : _children) {
        child->init();
    }
}
