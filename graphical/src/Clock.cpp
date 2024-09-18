/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Clock
*/

#include "Clock.hpp"

LE::Clock::Clock() : _lastFrame(std::chrono::high_resolution_clock::now()) {}

LE::Clock::~Clock() {}

std::size_t LE::Clock::restart()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastFrame).count();
    _lastFrame = now;
    return elapsed;
}

std::size_t LE::Clock::getElapsedTime() const
{
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastFrame).count();
}