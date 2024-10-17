/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** HitBox
*/

#pragma once

#include "BoxComponent.hpp"

/**
 * @brief A hit box component.
 *
 * This component represents a hit box.
 */
struct HitBox {
    int width;      ///< The width of the box.
    int height;     ///< The height of the box.
    std::bitset<NB_LAYERS> layers;      ///< The layers of the box.
    std::bitset<NB_MASKS> masks;        ///< The masks of the box.
};
