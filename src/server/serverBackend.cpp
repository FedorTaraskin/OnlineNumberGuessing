#include "serverBackend.hpp"
//Temporary for debugging
#include <iostream>
#include <exception>

bool Client::isConnected() { return connected; };
asio::ip::address_v4 Client::getIp() { return ip; };

void readClient(asio::ip::tcp::socket& mySocket) {
    std::string receivedData;
    receivedData.reserve(sizeof(header_t));
    asio::read(mySocket, asio::buffer(receivedData.data(), receivedData.size()));
    //header_t msgSize = *reinterpret_cast<header_t*>(receivedData.data());

    //WARNING: VERY DANGEROUS AND EXPERIMENTAL
    receivedData.reserve(*reinterpret_cast<header_t*>(receivedData.data()));
    std::cout << "Msg size: " << receivedData.size() << '\n';
    asio::read(mySocket, asio::buffer(receivedData.data(), receivedData.size()));
}

void acceptClients(){
    //Binds the server to 0.0.0.0:port on all network intefaces
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);

    asio::ip::tcp::acceptor acceptor(context, endpoint);

    while (true){
        try {
            asio::ip::tcp::socket mySocket(context);

            //This is the actuall waiting and connecting to a client
            acceptor.accept(mySocket);

            std::clog << "Client connected from: " << mySocket.remote_endpoint().address().to_string() << '\n';


        }
        catch (std::exception e) {
            //bind: ?¨õñºõü?ù ðô¨õ¸ ôû  ¸òþõóþ úþýªõú¸ªð ýõòõ¨õý.
            std::cerr << e.what();
        }
        catch (...) {
            std::cerr << "Weird error";
        }
    }
}
