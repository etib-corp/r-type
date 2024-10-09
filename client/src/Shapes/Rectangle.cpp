/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rectangle
*/

#include "Shapes/Rectangle.hpp"

LE::Shapes::Rectangle::Rectangle(float width, float height, float x, float y, Color *color)
{
    _color = color != nullptr ? color : new Color(LE::Color::FLOAT, 1.0f, 0.0f, 0.0f, 1.0f);
    _topLeft = new Triangle(Vector3<float>(x, y, 0), Vector3<float>(x + width, y, 0), Vector3<float>(x, y + height, 0), _color);
    _bottomRight = new Triangle(Vector3<float>(x + width, y, 0), Vector3<float>(x + width, y + height, 0), Vector3<float>(x, y + height, 0), _color);
    _height = height;
    _width = width;
}

LE::Shapes::Rectangle::~Rectangle()
{
}

void LE::Shapes::Rectangle::move(Vector3<float> offset)
{
    _topLeft->move(offset);
    _bottomRight->move(offset);
}

void LE::Shapes::Rectangle::init()
{
    _topLeft->init();
    _bottomRight->init();
}

void LE::Shapes::Rectangle::draw()
{
    _topLeft->draw();
    _bottomRight->draw();
}

void LE::Shapes::Rectangle::resize(float width, float height)
{
    _width = width;
    _height = height;

    float x = _topLeft->_p1.x;
    float y = _topLeft->_p1.y;

    _topLeft->_p1 = Vector3<float>(x, y, 0);
    _topLeft->_p2 = Vector3<float>(x + _width, y, 0);
    _topLeft->_p3 = Vector3<float>(x, y + _height, 0);

    _bottomRight->_p1 = Vector3<float>(x + _width, y, 0);
    _bottomRight->_p2 = Vector3<float>(x + _width, y + _height, 0);
    _bottomRight->_p3 = Vector3<float>(x, y + _height, 0);
}