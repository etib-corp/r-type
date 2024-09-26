/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Color
*/

#include "Color.hpp"

LE::Color::Color()
{
    _r = 1.0f;
    _g = 0.0f;
    _b = 0.0f;
    _a = 1.0f;
}

LE::Color::Color(float r, float g, float b, float a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

LE::Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    _r = r / 255.0f;
    _g = g / 255.0f;
    _b = b / 255.0f;
    _a = a / 255.0f;
}

LE::Color::Color(unsigned int hex, float a)
{
    _r = ((hex >> 16) & 0xFF) / 255.0f;
    _g = ((hex >> 8) & 0xFF) / 255.0f;
    _b = (hex & 0xFF) / 255.0f;
    _a = a;
}

void LE::Color::set(float r, float g, float b, float a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

void LE::Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    _r = r / 255.0f;
    _g = g / 255.0f;
    _b = b / 255.0f;
    _a = a / 255.0f;
}

void LE::Color::set(unsigned int hex, float a)
{
    _r = ((hex >> 16) & 0xFF) / 255.0f;
    _g = ((hex >> 8) & 0xFF) / 255.0f;
    _b = (hex & 0xFF) / 255.0f;
    _a = a;
}

LE::Color::~Color()
{
}
