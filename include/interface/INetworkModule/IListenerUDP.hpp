/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IListenerUDP
*/

#ifndef ILISTENERUDP_HPP_
#define ILISTENERUDP_HPP_

#include <memory>
#include "ISessionManager.hpp"

class IListenerUDP {
    public:
        virtual ~IListenerUDP() = default;

        void virtual run(std::shared_ptr<SessionManager> sessionManager) = 0;

        void virtual startReceive() = 0;

    protected:
        int _port;
        std::shared_ptr<SessionManager> _sessionManager;
    private:
};

#endif /* !ILISTENERUDP_HPP_ */
