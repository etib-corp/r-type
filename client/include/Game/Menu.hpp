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

class Menu : public LE::Scene {
    public:
        Menu();
        ~Menu();

        void play() override;

        void stop() override;

        class MainContainer : public LE::GUI::Container {
            public:
                MainContainer();
                ~MainContainer();
        };
};
