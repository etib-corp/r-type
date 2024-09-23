#include <iostream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cerrno>
#include <cstring>
#include <zlib.h>


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

void showRequest(Request header)
{
    std::cout << "Header:" << std::endl;
    std::cout << "\tMagicNumber: " << +header.MagicNumber << std::endl;
    std::cout << "\tECS_CLIENT_ID: " << +header.ECS_CLIENT_ID << std::endl;
    std::cout << "\tAction: " << +header.Action << std::endl;
    std::cout << "\tBodyLength: " << header.BodyLength << std::endl;
    std::cout << "\tBodyCorp: " << header.Body << std::endl;
}

void showBody(Entity *entity)
{
    std::cout << "Body:" << std::endl;
    std::cout << "\t" << entity->type << std::endl;
    std::cout << "\t" << entity->action << std::endl;
    std::cout << "\t" << entity->life << std::endl;
}

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

std::ostream& operator<<(std::ostream& os, const Request& req)
{
    std::vector<uint8_t> serializedData = PackUnpack::serialize(req);
    std::vector<uint8_t> packedData = PackUnpack::pack(serializedData);
    os.write(reinterpret_cast<const char*>(packedData.data()), packedData.size());
    return os;
}

std::istream& operator>>(std::istream& is, Request& req)
{
    size_t originalSize = sizeof(Request);
    std::vector<uint8_t> compressedData((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> decompressedData = PackUnpack::unPack(compressedData, originalSize);
    req = PackUnpack::deserialize<Request>(decompressedData);
    return is;
}

int _main(void)
{
    std::ostringstream oss;
    std::istringstream iss;
    Request requestFromSocket;
    Entity entity = {.type = "Avion", .action = "Voler", .life = 3};
    Request request = {0x0, 0x01, 0x05, 0x13, 0x0};
    ::memmove(request.Body, &entity, sizeof(Entity));

    std::cout << (sizeof(Entity) + strlen(entity.type) + strlen(entity.action) + 2 * sizeof(char)) << std::endl;

    oss << request;
    std::cout << oss.str().size() << std::endl;
    iss.str(oss.str());
    iss >> requestFromSocket;

    showRequest(request);
    showBody(&entity);
    showRequest(requestFromSocket);
    Entity *entityFromSocket = reinterpret_cast<Entity *>(requestFromSocket.Body);
    showBody(entityFromSocket);

    return 0;
}
