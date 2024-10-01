/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Box
*/

#pragma once

#include <bitset>
#include "Vector3.hpp"

#define NB_LAYERS 8     ///< Number of layers
#define NB_MASKS NB_LAYERS  ///< Number of masks

/**
 * @brief A box component.
 *
 * This component represents a box with width, height, depth, layers and masks.
 */
struct Box {
    int width;      ///< The width of the box.
    int height;     ///< The height of the box.
    int depth;      ///< The depth of the box.
    std::bitset<NB_LAYERS> layers;      ///< The layers of the box.
    std::bitset<NB_MASKS> masks;        ///< The masks of the box.
};