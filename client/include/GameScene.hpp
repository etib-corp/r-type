/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
    #define GAMESCENE_HPP_

    #include "Scene.hpp"
    #include "/home/sleo/etib/r-type/dependencies/lion-engine/lib/SFML/include/SFMLKeys.hpp"
    #include "interface/IEngine.hpp"
    #include "Utils.hpp"
    #include "EnumClass.hpp"

class GameScene : public LE::Scene {
    public:
        GameScene(LE::IEngine *engine);

        ~GameScene();

        void init() override;

    protected:
    private:
};

#endif /* !GAMESCENE_HPP_ */
