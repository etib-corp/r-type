/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Clock
*/

#pragma once

#include <chrono>
#include <cmath>

/**
 * @file Clock.hpp
 * @brief Defines the Clock class.
 */

namespace LE {
    /**
     * @class Clock
     * @brief The Clock class provides methods to restart the clock and get the elapsed time.
     *
     * The Clock class uses the high-resolution clock from the <chrono> library to measure time intervals.
     */
    class Clock {
        public:
            /**
             * @brief Default constructor for Clock.
             */
            Clock();

            /**
             * @brief Destructor for Clock.
             */
            ~Clock();

            /**
             * @brief Restarts the clock and returns the elapsed time since the last restart.
             * @return The elapsed time in milliseconds.
             */
            std::size_t restart();

            /**
             * @brief Gets the elapsed time since the last restart.
             * @return The elapsed time in milliseconds.
             */
            std::size_t getElapsedTime() const;
        private:
            std::chrono::high_resolution_clock::time_point _lastFrame; ///< The time point of the last frame.
    };
}