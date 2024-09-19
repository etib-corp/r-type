/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ISession
*/

#ifndef ISession_HPP_
#define ISession_HPP_

#include <string>

/**
 * @class ISession
 * @brief Interface for Session communication.
 *
 * This interface defines the basic operations for a Session, including reading
 * data and sending messages over TCP and UDP protocols.
 */
class ISession {
    public:
        virtual ~ISession() = default;

        virtual void read() = 0;

        virtual void sendTCP(const std::string &message) = 0;

        virtual void sendUDP(const std::string &message) = 0;

        int getId() const { return _id; }

        void setId(int id) { _id = id; }

    protected:
        int _id;
    private:
};

#endif /* !ISession_HPP_ */
