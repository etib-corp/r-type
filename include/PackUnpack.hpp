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

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>

class PackUnpack
{
public:
    PackUnpack() = delete;
    ~PackUnpack() = delete;
    [[nodiscard]] static std::vector<uint8_t> pack(const std::vector<uint8_t> &data) noexcept
    {
        namespace io = boost::iostreams;
        std::vector<uint8_t> compressedData;

        try
        {
            // Input stream to hold the original data
            std::stringstream inputStream;
            inputStream.write(reinterpret_cast<const char *>(data.data()), data.size());

            // Output stream to hold compressed data
            std::stringstream outputStream;

            // Create filtering stream buffer for compression
            io::filtering_streambuf<io::output> out;
            out.push(io::zlib_compressor());
            out.push(outputStream);

            // Compress data
            io::copy(inputStream, out);

            // Convert the output stream into a vector of bytes
            std::string compressedStr = outputStream.str();
            compressedData.assign(compressedStr.begin(), compressedStr.end());
        }
        catch (const boost::iostreams::zlib_error &e)
        {
            std::cerr << "Zlib compression error: " << e.what() << " (Error code: " << e.error() << ")" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error during packing: " << e.what() << std::endl;
        }

        return compressedData;
    }

    [[nodiscard]] static std::vector<uint8_t> unPack(const std::vector<uint8_t> &compressedData) noexcept
    {
        namespace io = boost::iostreams;
        std::vector<uint8_t> decompressedData;

        if (compressedData.empty())
        {
            std::cerr << "Error: No data to decompress." << std::endl;
            return decompressedData; // Return empty vector if there's nothing to decompress
        }

        try
        {
            // Input stream to hold the compressed data
            std::stringstream inputStream;
            inputStream.write(reinterpret_cast<const char *>(compressedData.data()), compressedData.size());

            // Output stream to hold decompressed data
            std::stringstream outputStream;

            // Create filtering stream buffer for decompression
            io::filtering_streambuf<io::input> in;
            in.push(io::zlib_decompressor());
            in.push(inputStream);

            // Decompress data
            io::copy(in, outputStream);

            // Convert the output stream into a vector of bytes
            std::string decompressedStr = outputStream.str();
            decompressedData.assign(decompressedStr.begin(), decompressedStr.end());
        }
        catch (const boost::iostreams::zlib_error &e)
        {
            std::cerr << "Zlib decompression error: " << e.what() << " (Error code: " << e.error() << ")" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error during unpacking: " << e.what() << std::endl;
        }

        return decompressedData;
    }
    template <typename T>
    [[nodiscard]] static std::vector<uint8_t> serialize(const T &obj)
    {
        std::vector<uint8_t> serializedData(sizeof(T));
        std::memmove(serializedData.data(), &obj, sizeof(T));
        return serializedData;
    }
    template <typename T>
    [[nodiscard]] static T deserialize(const std::vector<uint8_t> &data)
    {
        T obj;
        std::memmove(&obj, data.data(), sizeof(T));
        return obj;
    }

protected:
private:
};

#define BODY_LENGTH 1024

struct Header
{
    uint8_t MagicNumber;
    uint8_t EmmiterdEcsId;
    uint8_t ReceiverEcsId;
    uint8_t TopicID;
    uint8_t Action;
    uint32_t BodyLength;
};

struct Body
{
    uint8_t _buffer[BODY_LENGTH + 1];
};

struct Request
{
    Header header;
    Body body;
};

struct _Entity
{
    char type[256];
    char action[256];
    int life;
};

std::ostream &operator<<(std::ostream &os, const Body &req);

std::istream &operator>>(std::istream &is, Body &req);

void showHeader(Header header);

void showBody(_Entity *entity);

#endif /* !PACKUNPACK_HPP_ */
