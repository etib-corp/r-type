#include "message/Message.hpp"

Message::Message(void) : _emmiter_id(0), _receiver_id(0), _topic_id(0), _action(0)
{
}

Message::~Message(void)
{
}

static std::string serializeRequest(Request &request)
{
    std::ostringstream oss;

    oss.write(reinterpret_cast<const char*>(&request.header), sizeof(request.header));
    oss.write(reinterpret_cast<const char*>(&request.body), sizeof(uint8_t) * request.header.BodyLength);
    return oss.str();
}

static std::string compressAndPrepare(Header header, Body body)
{
    Request request;
    std::ostringstream oss;

    oss << body;
    ::memmove(&request.header, &header, sizeof(Header));
    ::memmove(&request.body, oss.str().c_str(), sizeof(Body));
    request.header.BodyLength = oss.str().size();
    return serializeRequest(request);
}

std::string Message::serialize(void) const
{
    Header header = {0};
    Body body = {0};

    header.EmmiterdEcsId = _emmiter_id;
    header.ReceiverEcsId = _receiver_id;
    header.Action = _action;
    header.BodyLength = 0;
    std::memset(body._buffer, 0, 1024);
    return compressAndPrepare(header, body);
}
