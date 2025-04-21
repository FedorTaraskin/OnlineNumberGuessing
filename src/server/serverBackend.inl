#pragma once
#include "globals.hpp"
#include "serializer.hpp"
#include <chrono>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <list>
#include "comm.hpp"
#include "serverShared.hpp"

#ifdef _DEBUG
#include <iostream> // For showing errors easily. Wrong, but simple & quick.
#endif

inline std::vector<sLobby> lobbies;

// Clients that have connected to the server, but are in no lobby.
inline std::list<sClient> idleClients;

inline void sanAndStoreClient() {
    bool validName;
    std::string clientName;

    do {
        clientName = comm::read<std::string>().parameter;
        validName = isValidName(clientName);
        comm::send(Packet<bool>{static_cast<action_t>(actions::approveName), validName});
    } while (!validName);
}

// To be run in parallel by each client's thread; listens to
// their packets and responds accordingly.
inline void serveClient() {

}

void acceptClients(){
    // Binds the server to 0.0.0.0:port on all network intefaces
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);

    // Makes an acceptor (for letting clients connect)
    asio::ip::tcp::acceptor acceptor(comm::context, endpoint);

    while (true) {
        idleClients.emplace_back();
        try {
            // Makes a socket that will be used for just one client, don't reuse
            asio::ip::tcp::socket clientSocket(comm::context);

            // This is the actual waiting and connecting to a client
            acceptor.accept(clientSocket);

            std::clog << "Client connected from: "
                << clientSocket.remote_endpoint().address().to_string() << '\n';

            //idleClients.emplace_back(std::string(), clientSocket.remote_endpoint().address().to_v4());
            
            // Makes a separate thread that will force the user to choose
            // a valid name before placing him into idleClients.
            //std::jthread nameSanThread(sanAndStoreClient, std::ref(clientSocket));

            // Lets the thread continue working even when it goes out of scope
            //nameSanThread.detach();
        }
        catch (asio::system_error& e) {
            std::cerr << "ERROR: " << e.what() << '\n';
        }
    }
}

inline bool isValidName(std::string_view name) {

    // Does a client with the same name exist in a lobby?
    for (sLobby& lobby : lobbies) {
        for (sClient& client : lobby.players) {
            if (client.name == name) return false;
        }
    }

    // Is a client with the same name idle?
    for (sClient& client : idleClients) {
        if (client.name == name) return false;
    }

    // If it is a valid name (no previous condition met).
    return true;
}

inline int rng(int min, int max) {
    #ifdef HUGE_NUMBER_GEN
    // The MOST overkill RNG possible for this!
    // Almost 5kb big, and the implementation is... something, jeez
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
    using namespace asio::ip;

    inline const unsigned int delaySec = 1;
    static std::stop_token st;
    static std::jthread thr;
    
    // Create broadcast endpoint
    static udp::endpoint broadcastEndpoint(address_v4::broadcast(), port);

    // Create socket.
    static udp::socket broadcastSocket(comm::context, udp::v4());


    // Blocking, to be run on a separate thread.
    // Not meant to be used outside of this file.
    static void announceWithDelay(unsigned int sec) {
        while (!st.stop_requested()) {
            announceSelf();
            std::this_thread::sleep_for(std::chrono::seconds(sec));
        }
    }

    // Non-blocking
    void start() {
        if (!st.stop_possible()) {

            // Open socket in udp-v4 mode
            //broadcastSocket.open(udp::v4());

            // Enable broadcast option in broadcastSocket
            broadcastSocket.set_option(asio::socket_base::broadcast(true));

            // Start thread on stack
            thr = std::move(std::jthread(announceWithDelay, delaySec));

            // The stop token is a copyable object that lets us signal
            // to the thread to stop.
            st = thr.get_stop_token();
        }
    }

    // Non-blocking
    void stop() {
        if (!st.stop_requested()) {
            thr.request_stop();
            thr.join();
        }
    }

    // Blocking but quick, a single announcement
    void announceSelf() {
        #ifdef _DEBUG
        std::clog << "Server announcing...\n";
        #endif // _DEBUG

        // Send broadcast msg
        broadcastSocket.send_to(asio::buffer(serializedServerTag), broadcastEndpoint);
    }
}