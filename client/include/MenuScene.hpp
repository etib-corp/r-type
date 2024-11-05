/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP_
#define MENUSCENE_HPP_

#include "Scene.hpp"
#include "interface/IEngine.hpp"

class MenuScene : public LE::Scene {
    public:
        MenuScene(LE::IEngine *engine);
        ~MenuScene();

        void init() override;

    protected:
    private:
};

#endif /* !MENUSCENE_HPP_ */
