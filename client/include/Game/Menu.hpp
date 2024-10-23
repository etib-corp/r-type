/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Menu
*/

#pragma once

#include "Engine.hpp"
#include "Scene.hpp"

#include "Color.hpp"

#include "GUI/Button.hpp"
#include "GUI/TextField.hpp"

#include <regex>

class Menu : public LE::Scene {
    public:
        /**
         * @brief Constructs a new Menu object.
         *
         * This constructor initializes the Menu object. The Menu is used in the R-Type Game.
         */
        Menu();

        /**
         * @brief Destructor for the Menu class.
         */
        ~Menu();

        bool isValidIP(const std::string &ip);

        /**
         * @brief Class in which all the GUI elements are stored for the Menu scene.
         */
        class MainContainer : public LE::GUI::Container {
            public:
                /**
                 * @brief Constructs a new MainContainer object.
                 */
                MainContainer();

                /**
                 * @brief Destructor for the MainContainer class.
                 */
                ~MainContainer();
        };
};
