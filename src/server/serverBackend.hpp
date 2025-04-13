#pragma once

#include "globals.hpp"
#include "serializer.hpp"
#include <asio.hpp>
#include <chrono>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#ifdef _DEBUG
#include <iostream> // For showing errors easily. Wrong, but simple & quick.
#endif

inline asio::io_context context;

// For the sake of simplicity and getting this program done before the end of the year,
// we use syncronous i/o with threads. Fine for a few clients, horrible for many.
// We utilize exclusively ipv4 in this project.
// UDP for broadcasting (server discovery), TCP for everything else.

inline std::vector<Lobby> lobbies;

// Clients that have connected to the server, but are in no lobby.
inline std::vector<Client> idleClients;

inline void readClient(asio::ip::tcp::socket& mySocket);
void acceptClients();

inline int rng(int min, int max);

// Functionality for clients to discover the server automatically on LAN.
namespace announce {
	inline const unsigned int delaySec = 1;
	extern void start(); //Repeated announcements
	extern void stop();
	extern void announceSelf(); //Single announcement
}