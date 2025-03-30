//"Main" file for the client
#include "asio.hpp"
#include "globals.hpp" //Not to be confused with 'global.hpp', which is ASIO-internal.
#include <cstring>
#include <iostream>
#include <string>

asio::io_context context;
asio::ip::tcp::resolver resolver(context);
asio::ip::tcp::resolver::results_type dnsResult = resolver.resolve("localhost", std::to_string(port));
asio::ip::address_v4 serverAddress;

asio::ip::tcp::socket mySocket(context);

char msg[] = "Hello from client!";

int main() {
    //std::cout << "Bienvenido! Elija un servidor de los siguientes o escriba \"auto\" para automaticamente eligir el primer servidor disponible:\n";
    try {
        mySocket.connect(*dnsResult.begin());
    }
    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        asio::write(mySocket, asio::buffer(msg, std::strlen(msg)));
    }
    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
