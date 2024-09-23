/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IListenerUDP
*/

#ifndef ILISTENERUDP_HPP_
#define ILISTENERUDP_HPP_

class IServer;

class IListenerUDP {
    public:
        virtual ~IListenerUDP() = default;

        void virtual run(IServer *server) = 0;

        void virtual startReceive() = 0;

    protected:
        int _port;
        IServer *_server;
    private:
};

#endif /* !ILISTENERUDP_HPP_ */
