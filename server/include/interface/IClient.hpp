/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** IClient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include <string>

/**
 * @class IClient
 * @brief Interface for client communication.
 *
 * This interface defines the basic operations for a client, including reading
 * data and sending messages over TCP and UDP protocols.
 */
class IClient {
    public:
        virtual ~IClient() = default;

        virtual void read() = 0;

        virtual void sendTCP(const std::string &message) = 0;

        virtual void sendUDP(const std::string &message) = 0;

        int getId() const { return _id; }

        void setId(int id) { _id = id; }

    protected:
        int _id;
    private:
};

#endif /* !ICLIENT_HPP_ */
