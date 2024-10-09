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

LE::Color::Color(UseMode mode, float r, float g, float b, float a)
{
    if (mode == UseMode::CHAR) {
        if (r > 255 || g > 255 || b > 255 || a > 255)
            throw ColorError("Color values must be in the range [0, 255]");
        if (r < 0 || g < 0 || b < 0 || a < 0)
            throw ColorError("Color values must be in the range [0, 255]");
        _r = r / 255.0f;
        _g = g / 255.0f;
        _b = b / 255.0f;
        _a = a / 255.0f;
    } else {
        if (r > 1 || g > 1 || b > 1 || a > 1)
            throw ColorError("Color values must be in the range [0, 1]");
        if (r < 0 || g < 0 || b < 0 || a < 0)
            throw ColorError("Color values must be in the range [0, 1]");
        _r = r;
        _g = g;
        _b = b;
        _a = a;
    }
}

// LE::Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
// {
//     _r = r / 255.0f;
//     _g = g / 255.0f;
//     _b = b / 255.0f;
//     _a = a / 255.0f;
// }

LE::Color::Color(unsigned int hex, float a)
{
    _r = ((hex >> 16) & 0xFF) / 255.0f;
    _g = ((hex >> 8) & 0xFF) / 255.0f;
    _b = (hex & 0xFF) / 255.0f;
    _a = a;
}

void LE::Color::set(UseMode mode, float r, float g, float b, float a)
{
    if (mode == UseMode::CHAR) {
        if (r > 255 || g > 255 || b > 255 || a > 255)
            throw ColorError("Color values must be in the range [0, 255]");
        if (r < 0 || g < 0 || b < 0 || a < 0)
            throw ColorError("Color values must be in the range [0, 255]");
        _r = r / 255.0f;
        _g = g / 255.0f;
        _b = b / 255.0f;
        _a = a / 255.0f;
    } else {
        if (r > 1 || g > 1 || b > 1 || a > 1)
            throw ColorError("Color values must be in the range [0, 1]");
        if (r < 0 || g < 0 || b < 0 || a < 0)
            throw ColorError("Color values must be in the range [0, 1]");
        _r = r;
        _g = g;
        _b = b;
        _a = a;
    }
}

// void LE::Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
// {
//     _r = r / 255.0f;
//     _g = g / 255.0f;
//     _b = b / 255.0f;
//     _a = a / 255.0f;
// }

void LE::Color::set(unsigned int hex, float a)
{
    _r = ((hex >> 16) & 0xFF) / 255.0f;
    _g = ((hex >> 8) & 0xFF) / 255.0f;
    _b = (hex & 0xFF) / 255.0f;
    _a = a;
}

LE::Vector4<float> LE::Color::toVector4() const
{
    return Vector4<float>(_r, _g, _b, _a);
}

LE::Color::~Color()
{
}
