// "Main" client file
#include "clientBackend.hpp"
#include "globals.hpp" //Not to be confused with 'global.hpp', which is ASIO-internal.
#include "serializer.hpp"
#include <asio.hpp>
#include <iostream>
#include "comm.hpp"
#include "packet.hpp"
#include <string>

std::string name;

int main() {
    std::cout << "Bienvenido! Escriba su nombre: ";
    std::getline(std::cin, name);
    try {
        std::clog << "Finding server...\n";
        asio::ip::address_v4 serverAddress = getServerIp();
        std::clog << "Found server at " << serverAddress.to_string() << '\n';
        mainSocket.connect(asio::ip::tcp::endpoint(serverAddress, port));
        std::clog << "Connected to server.\n";

        forceAvailableName(name, mainSocket);
        
        // Receive lobbies
        std::vector<cLobby> lobbies = getLobbies(mainSocket);
        
    }
    catch (asio::system_error& e) {
        std::cerr << e.what() << '\n';
    }
}
