/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IListenerUDP
*/

#ifndef ILISTENERUDP_HPP_
#define ILISTENERUDP_HPP_

class INetworkModule;

class IListenerUDP {
    public:
        virtual ~IListenerUDP() = default;

        void virtual run(INetworkModule *_networkModule) = 0;

        void virtual startReceive() = 0;

    protected:
        int _port;
        INetworkModule *_networkModule;
    private:
};

#endif /* !ILISTENERUDP_HPP_ */
