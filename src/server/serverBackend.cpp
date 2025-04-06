#include "serverBackend.hpp"

bool Client::isConnected() { return connected; };
asio::ip::address_v4 Client::getIp() { return ip; };

void readClient(asio::ip::tcp::socket& mySocket) {
    std::string receivedData;
    receivedData.reserve(sizeof(header_t));
    asio::read(mySocket, asio::buffer(receivedData.data(), sizeof(header_t)));
    std::clog << "Got header! ";
    header_t size = deserialize(receivedData)
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

            readClient(mySocket);
        }
        catch (std::exception e) {
            std::cerr << "ERROR: " << e.what() << '\n';
        }
        catch (...) {
            std::cerr << "Weird error";
        }
    }
}

inline int rng(int min, int max) {
    #ifdef HUGE_NUMBER_GEN
    //The MOST overkill RNG possible for this!
    //Almost 5kb big, and the implementation is... something, jeez
    static std::mt19937 rng(std::random_device{}());
    #else
    static std::minstd_rand rng(std::random_device{}());
    #endif
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}