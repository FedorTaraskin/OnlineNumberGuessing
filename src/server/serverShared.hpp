#pragma once
// Shared things - server only
#include <string>
#include <asio.hpp>
#include <thread>
#include "comm.hpp"
#include <vector>
#include <type_traits>

extern void serveClient(); // In serverBackend.hpp

// Server's view of a client.
struct sClient {
	std::string name;
	asio::ip::address_v4 ip;
	asio::ip::tcp::socket cSock;
	std::jthread thr;

	// Default constructor
	sClient() : cSock(comm::context) { 
		thr = std::move(std::jthread(serveClient)); 
	}
	
	// Move constructor
	sClient(sClient&&) = default;

	// Move assignment operator
	sClient& operator=(sClient&&) = default;

	// NO copy constructor; this class is heavy.
	sClient(const sClient&) = delete;

	// NO copy assignment operator; same reason.
	// WARNING! SLOW!
	// But for some reason necessary, even if not copying
	sClient& operator=(const sClient&) = default;

	~sClient();

	// To be run in parallel by each client's thread; listens to
	// their packets and responds accordingly.
	inline void serve();
};

// (S)erver's view of a lobby.
// Has more info than the clients view of a lobby.
struct sLobby {
	std::vector<sClient> players;
	std::string name;
};