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
struct HurtBox : Box {
    std::function<void()> onHit;     ///< The function to call when the hurt box is hit.
};
