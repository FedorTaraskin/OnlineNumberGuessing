//"Main" file for the client
#include <asio.hpp>
#include "globals.hpp" //Not to be confused with 'global.hpp', which is ASIO-internal.
#include "packet.hpp"
#include <cstring>
#include <iostream>
#include <string>
#include <cereal/archives/portable_binary.hpp>
#include "serializer.hpp"

asio::io_context context;
asio::ip::address_v4 serverAddress = asio::ip::make_address_v4("127.0.0.1");
asio::ip::tcp::socket mySocket(context);

char msg[] = "Hello from client!";
Packet firstPacket(msg);
std::string serializedPacket = serialize(firstPacket);
header_t serializedPacketHeader = serializedPacket.size();

int main() {
    //std::cout << "Bienvenido! Elija un servidor de los siguientes o escriba \"auto\" para automaticamente eligir el primer servidor disponible:\n";
    try {
        mySocket.connect({ serverAddress, port });
        std::clog << "Connected to server.\n";
        //Send size
        asio::write(mySocket, asio::buffer(&serializedPacketHeader, sizeof(header_t)));
        //Send packet
        asio::write(mySocket, asio::buffer(serializedPacket.data(), serializedPacketHeader));
    }
    catch (asio::system_error& e) {
        std::cerr << e.what() << '\n';
    }
}
