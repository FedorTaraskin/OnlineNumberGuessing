// "Main" client file
#include "clientBackend.hpp"
#include "globals.hpp" //Not to be confused with 'global.hpp', which is ASIO-internal.
#include "serializer.hpp"
#include <asio.hpp>
#include <iostream>
#include "packet.hpp"
#include <string>

std::string serializedPacket = g_Serialize(std::string("Hello from client!"));
std::string serializedPacketHeader = g_Serialize(static_cast<header_t>(serializedPacket.size()));
std::string name;

int main() {
    std::cout << "Bienvenido! Escriba su nombre: ";
    std::getline(std::cin, name);
    try {
        std::clog << "Finding server...\n";
        asio::ip::address_v4 serverAddress = getServerIp();
        std::clog << "Found server at " << serverAddress.to_string() << '\n';
        comm::mainSocket.connect(asio::ip::tcp::endpoint(serverAddress, port));
        std::clog << "Connected to server.\n";

        // Send client name
        Packet<std::string> namePacket(actions::sendName, name);
        namePacket.send(comm::mainSocket);

        // Check whether a client with the same name exists.
        // If true, force user to rechoose a name.

        
        // Receive lobbies
        
    }
    catch (asio::system_error& e) {
        std::cerr << e.what() << '\n';
    }
    system("pause");
}
