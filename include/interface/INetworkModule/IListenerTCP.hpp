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

class IServer;

class IListenerTCP {
    public:
        virtual ~IListenerTCP() = default;

        virtual void WaitForConnection() = 0;

        virtual void run(IServer* module) = 0;

    protected:
        IServer *_server;
    private:
};

#endif /* !ILISTENERTCP_HPP_ */
