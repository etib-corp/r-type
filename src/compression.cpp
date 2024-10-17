#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cerrno>
#include <cstring>
#include "PackUnpack.hpp"

void showHeader(Header header)
{
    std::cout << "Header:" << std::endl;
    std::cout << "\tMagicNumber: " << +header.MagicNumber << std::endl;
    std::cout << "\tEmmiter id: " << +header.EmmiterdEcsId << std::endl;
    std::cout << "\tReceiver id: " << +header.ReceiverEcsId << std::endl;
    std::cout << "\tAction: " << +header.Action << std::endl;
    std::cout << "\tBodyLength: " << header.BodyLength << std::endl;
    // std::cout << "\tBodyCorp: " << header.Body << std::endl;
}

void showBody(_Entity *entity)
{
    std::cout << "Body:" << std::endl;
    std::cout << "\t" << entity->type << std::endl;
    std::cout << "\t" << entity->action << std::endl;
    std::cout << "\t" << entity->life << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Body &req)
{
    std::vector<uint8_t> serializedData = PackUnpack::serialize(req);
    std::vector<uint8_t> packedData = PackUnpack::pack(serializedData);
    os.write(reinterpret_cast<const char *>(packedData.data()), packedData.size());
    return os;
}

std::istream &operator>>(std::istream &is, Body &req)
{
    size_t originalSize = sizeof(Body);
    std::vector<uint8_t> compressedData((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> decompressedData = PackUnpack::unPack(compressedData);
    req = PackUnpack::deserialize<Body>(decompressedData);
    return is;
}
