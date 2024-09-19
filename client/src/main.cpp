#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"

int main(void)
{
    std::string pathLib = getPathOfNetworkDynLib() + getExtensionKernel();

    try {
        LoaderLib lb(pathLib, "");

        lb.LoadModule();

        IClient *client = lb.createClient();

        client->connectToServer("127.0.0.1", 8080);
        client->sendTCP("Hello from client TCP\n");
        client->sendUDP("Hello from client UDP\n");
        while (true)
        {
        }

    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
