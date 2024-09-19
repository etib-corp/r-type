/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IListenerTCP
*/

#ifndef ILISTENERTCP_HPP_
#define ILISTENERTCP_HPP_

#include <queue>
#include <memory>

class INetworkModule;

class IListenerTCP {
    public:
        virtual ~IListenerTCP() = default;

        virtual void WaitForConnection() = 0;

        virtual void run(INetworkModule* module) = 0;

    protected:
        INetworkModule *_module;
    private:
};

#endif /* !ILISTENERTCP_HPP_ */
