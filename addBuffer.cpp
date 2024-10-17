#include <iostream>
#include <cstring>
#include <stdexcept>

#define BUFFER_SIZE 8192

struct Data {
    int id;
    float value;
};

struct Vector3D {
    float x;
    float y;
    float z;
};

struct Entity {
    int id;
    double collision;
};

class Buffer {
    public:
        Buffer() : _cursorIndex(0)
        {
            ::memset(_buffer, 0, BUFFER_SIZE);
        }

        template <typename T>
        void add(const T& data)
        {
            size_t dataSize = sizeof(T);

            if ((_cursorIndex + dataSize) > BUFFER_SIZE)
            {
                throw std::runtime_error("Throw qu'il n'y a plus d'espace stv");
            }

            ::memmove(&_buffer[_cursorIndex], &data, dataSize);
            _cursorIndex += dataSize;
        }

        void print() const
        {
            for (size_t i = 0; i < _cursorIndex; ++i)
            {
                std::cout << std::hex << (int)_buffer[i] << " ";
            }
            std::cout << std::dec << std::endl;
        }

        template <typename T>
        T get(size_t index) const
        {
            if ((index + sizeof(T)) > _cursorIndex)
            {
                throw std::runtime_error("Throw invalid read of size ...");
            }

            T data;
            ::memmove(&data, &_buffer[index], sizeof(T));
            return data;
        }

        private:
            char _buffer[8192];
            size_t _cursorIndex;
};

int main(void)
{
    Buffer buffer;
    Buffer secondBuffer;

    int intValue = 42;
    float floatValue = 3.14f;
    Vector3D vec3 = {.x = 0.1f, .y = 0.3f, .z = 0.4f};
    Entity entity = {.id = 30, .collision = 1.75};

    buffer.add(intValue);
    buffer.add(floatValue);
    buffer.add(vec3);
    buffer.add(entity);

    buffer.print();

    // SIMULE RECEIVE DATA ON SOCKET
    const char *data = reinterpret_cast<char *>(&buffer);
    ::memmove(&secondBuffer, data, sizeof(Buffer));

    secondBuffer.print();

    int recoveredInt = secondBuffer.get<int>(0);
    float recoveredFloat = secondBuffer.get<float>(sizeof(int));
    Vector3D recoveredVec3 = secondBuffer.get<Vector3D>(sizeof(int) + sizeof(float));
    Entity recoveredEnity = secondBuffer.get<Entity>(sizeof(int) + sizeof(float) + sizeof(Vector3D));

    std::cout << "test int : " << recoveredInt << "\n";
    std::cout << "test float : " << recoveredFloat << "\n";
    std::cout << "test Vector3D : x=" << recoveredVec3.x << ", y=" << recoveredVec3.y << ", z=" << recoveredVec3.z << "\n";
    std::cout << "test Person : age=" << recoveredEnity.id << ", height=" << recoveredEnity.collision << "\n";

    return 0;
}
