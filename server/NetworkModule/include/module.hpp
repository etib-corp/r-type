/*
** EPITECH PROJECT, 2024
** interfaceRtype
** File description:
** module
*/

#ifndef MODULE_HPP_
#define MODULE_HPP_

#include "interface/INetworkModule.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include "ConnectionTCP.hpp"
#include <memory>
#include "ConnectionUDP.hpp"
#include "ConnectionUDP.hpp"

class module : public INetworkModule {
    public:
        module();
        ~module();

        void run() override;
    protected:
        std::shared_ptr<ConnectionTCP> _connectionTCP;
        std::shared_ptr<ConnectionUDP> _connectionUDP;
    private:
};

#endif /* !MODULE_HPP_ */
