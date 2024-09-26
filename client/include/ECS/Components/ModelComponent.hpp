/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Render
*/

#pragma once

#include "Shader.hpp"

struct ModelComponent {
    std::shared_ptr<LE::Shader> shader; ///< The shader of the model
};