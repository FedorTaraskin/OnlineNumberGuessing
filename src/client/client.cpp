//"Main" file for the client
#include <asio.hpp>
#include "globals.hpp" //Not to be confused with 'global.hpp', which is ASIO-internal.
#include <iostream>
#include <string>
#include "serializer.hpp"
#include "clientGlobals.hpp"
#include "clientBackend.hpp"

//Temporals
#include <cstdlib> //For system()
#include <cassert>

std::string serializedPacket = serialize(std::string("Hello from client!"));
std::string serializedPacketHeader = serialize(static_cast<header_t>(serializedPacket.size()));

int main() {
    //std::cout << "Bienvenido! Elija un servidor de los siguientes o escriba \"auto\" para automaticamente eligir el primer servidor disponible:\n";
    #ifdef _DEBUG
    std::clog << "Binary size of header is: " << serializedPacketHeader.size() << "\nAnd its raw representation is: " << serializedPacketHeader << '\n';
    assert(serializedPacketHeader.size() == headerRawSize && "Header size is not correct");
    #endif
    try {
        std::clog << "Finding server...\n";
        asio::ip::address_v4 serverAddress = getServerIp();
        std::clog << "Found server at " << serverAddress.to_string() << '\n';
        mySocket.connect(asio::ip::tcp::endpoint( serverAddress, port ));
        std::clog << "Connected to server.\n";
        //Send size
        std::clog << "Sending size: " << serializedPacket.size() << '\n';
        asio::write(mySocket, asio::buffer(serializedPacketHeader, serializedPacketHeader.size()));
        //Send packet
        asio::write(mySocket, asio::buffer(serializedPacket, serializedPacket.size()));
    }
    catch (asio::system_error& e) {
        std::cerr << e.what() << '\n';
    }
    system("pause");
}
