#pragma once

#include <asio.hpp>
#include <vector>
#include "globals.hpp"
#include "serializer.hpp"
#include "comm.hpp"

// Temp
#include <iostream>
#include <stdexcept>

// Blocks thread until server is discovered.
asio::ip::address_v4 getServerIp();

// This "Lobby" struct is different from a server's Lobby struct.
// The server additionally stores IPs, threads and sockets for each client.
struct cLobby {
	std::string name;
	std::vector<std::string> clients;
};

inline std::vector<cLobby> getLobbies();