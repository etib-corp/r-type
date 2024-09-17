/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ANetworkModule
*/

#ifndef ANETWORKMODULE_HPP_
#define ANETWORKMODULE_HPP_

class INetworkModule {
    public:
        virtual ~INetworkModule() = default;

        virtual void run() = 0;

    protected:
    private:
};

#endif /* !ANETWORKMODULE_HPP_ */
