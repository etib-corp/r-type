/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** HurtBox
*/

#pragma once

#include "ECS/Components/BoxComponent.hpp"

/**
 * @brief A hurt box component.
 *
 * This component represents a hurt box.
 */
struct HurtBox {
    int width;      ///< The width of the box.
    int height;     ///< The height of the box.
    std::bitset<NB_LAYERS> layers;      ///< The layers of the box.
    std::bitset<NB_MASKS> masks;        ///< The masks of the box.
    std::function<void()> onHit;     ///< The function to call when the hurt box is hit.
};
