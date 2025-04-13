#include "serverBackend.hpp"

template <typename Data>
Data readClient(asio::ip::tcp::socket& mySocket) {
    std::string buffer;
    // Resize to fit the header in binary form
    buffer.resize(headerRawSize);

    // Read the header and deserialize it
    asio::read(mySocket, asio::buffer(buffer.data(), headerRawSize));
    header_t size = deserialize<header_t>(buffer);

    // The header tells us how much data is about to be sent.
    // Resize to fit all the data to be received.
    buffer.resize(size);

    // Read data and deserialize it
    asio::read(mySocket, asio::buffer(buffer.data(), size));
    return deserialize<Data>(buffer);
}

void acceptClients(){
    //Binds the server to 0.0.0.0:port on all network intefaces
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);

    asio::ip::tcp::acceptor acceptor(context, endpoint);

    while (true){
        try {
            asio::ip::tcp::socket mySocket(context);

            //This is the actual waiting and connecting to a client
            acceptor.accept(mySocket);

            std::clog << "Client connected from: "
                << mySocket.remote_endpoint().address().to_string() << '\n';

            std::string clientName = readClient<std::string>(mySocket);

            idleClients.emplace_back(mySocket.remote_endpoint().address().to_v4(), clientName);

        }
        catch (std::runtime_error e) {
            std::cerr << "ERROR: " << e.what() << '\n';
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

// Namespace for the announcement functionality.
// "Announcement" = broadcasting a signal on the entire LAN, 
// for clients to receive and connect.
namespace announce {
    std::stop_token st;
    std::jthread* thrPtr;

    // Blocking, to be run on a separate thread.
    // Not meant to be used outside of this file.
    static void announceWithDelay(unsigned int sec) {
        while (!st.stop_requested()) {
            announceSelf();
            std::this_thread::sleep_for(std::chrono::seconds(sec));
        }
    }

    //Non-blocking
    void start() {
        if (thrPtr == nullptr) {
            thrPtr = new std::jthread(announceWithDelay, delaySec);
            st = thrPtr->get_stop_token();
        }
    }

    //Non-blocking
    void stop() {
        if (!st.stop_requested()) {
            thrPtr->request_stop();
            thrPtr->join();
            delete thrPtr;
        }
    }

    //Blocking but quick, a single announcement
    void announceSelf() {
        #ifdef _DEBUG
        std::clog << "Server announcing...\n";
        #endif // _DEBUG

        using namespace asio::ip;
        //Create broadcast endpoint
        udp::endpoint broadcastEndpoint(address_v4::broadcast(), port);

        //Create socket.
        udp::socket socket(context);

        //Open socket in udp-v4 mode
        socket.open(udp::v4());

        //Enable broadcast option in socket
        socket.set_option(asio::socket_base::broadcast(true));

        //We do not need to bind to send broadcasts, only to receive
        //socket.bind(broadcastEndpoint);

        //Send broadcast msg
        const std::string serializedServerTag = serialize(serverTag);
        socket.send_to(asio::buffer(serializedServerTag), broadcastEndpoint);
    }
}