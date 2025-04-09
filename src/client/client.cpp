//"Main" file for the client
#include <asio.hpp>
#include "globals.hpp" //Not to be confused with 'global.hpp', which is ASIO-internal.
#include "packet.hpp"
#include <cstring>
#include <iostream>
#include <string>
#include "serializer.hpp"

#include <stdint.h> //For UINT16_MAX

asio::io_context context;
asio::ip::address_v4 serverAddress = asio::ip::make_address_v4("127.0.0.1");
asio::ip::tcp::socket mySocket(context);

std::string msg = "Hello from client!";
std::string serializedPacket = serialize(msg);
std::string serializedPacketHeader = serialize(static_cast<header_t>(serializedPacket.size()));

int main() {
    //std::cout << "Bienvenido! Elija un servidor de los siguientes o escriba \"auto\" para automaticamente eligir el primer servidor disponible:\n";
    //std::clog << "Binary size of header is: " << serializedPacketHeader.size() << "\nAnd its raw representation is: " << serializedPacketHeader << '\n';
    try {
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
