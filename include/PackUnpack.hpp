/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PackUnpack
*/

#ifndef PACKUNPACK_HPP_
#define PACKUNPACK_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cerrno>
#include <cstring>
#include <zlib.h>

class PackUnpack {
    public:
        PackUnpack() = delete;
        ~PackUnpack() = delete;
        [[nodiscard]] static std::vector<uint8_t> pack(const std::vector<uint8_t>& data) noexcept
        {
            uLongf compressedSize = compressBound(data.size());
            std::vector<uint8_t> compressedData(compressedSize);

            if (compress2(compressedData.data(), &compressedSize, data.data(), data.size(), Z_BEST_COMPRESSION) != Z_OK) {
                // throw std::runtime_error("Compression failed!");
            }

            compressedData.resize(compressedSize);
            return compressedData;
        }
        [[nodiscard]] static std::vector<uint8_t> unPack(const std::vector<uint8_t>& compressedData, size_t originalSize) noexcept
        {
            std::vector<uint8_t> decompressedData(originalSize);

            if (uncompress(decompressedData.data(), &originalSize, compressedData.data(), compressedData.size()) != Z_OK) {
                // throw std::runtime_error("Decompression failed!");
            }

            decompressedData.resize(originalSize);
            return decompressedData;
        }
        template<typename T>
        static std::vector<uint8_t> serialize(const T& obj)
        {
            std::vector<uint8_t> serializedData(sizeof(T));
            std::memmove(serializedData.data(), &obj, sizeof(T));
            return serializedData;
        }
        template<typename T>
        static T deserialize(const std::vector<uint8_t>& data)
        {
            T obj;
            std::memmove(&obj, data.data(), sizeof(T));
            return obj;
        }
    protected:
    private:
};

struct Request {
    uint8_t MagicNumber;
    uint8_t ECS_CLIENT_ID;
    uint8_t Action;
    uint32_t BodyLength;
    uint8_t Body[1024];
};

struct Entity {
    char type[256];
    char action[256];
    int life;
};


std::ostream& operator<<(std::ostream& os, const Request& req);

std::istream& operator>>(std::istream& is, Request& req);

void showRequest(Request header);

void showBody(Entity *entity);

#endif /* !PACKUNPACK_HPP_ */
