/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Rtype
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include "interface/IEngine.hpp"
#include "CallbackClient.hpp"

class Rtype : public LE::IGame {
    public:
        Rtype();
        ~Rtype();

        void init(LE::IEngine &engine) override;

        void update() override;

    protected:
    private:
};

#endif /* !RTYPE_HPP_ */
