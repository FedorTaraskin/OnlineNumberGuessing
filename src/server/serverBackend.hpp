#pragma once
//A header file that includes all the functionality in the "server" folder.
//There is also a "serverFrontend.cpp" file in this directory: it is an example use case of this.

//Uncomment the following line for a more sophisticated random algorithm;
//#define HUGE_NUMBER_GEN

#include "serverGlobals.hpp"
#include <vector>
#include "asio.hpp"
#include <thread>
#include "globals.hpp"
#include <random>
#include <iostream> //For showing errors easily. Wrong, but simple & quick.
#include <exception>

//For the sake of simplicity and getting this program done before the end of the year,
//we use syncronous i/o with threads. Fine for a few clients, horrible for many.

inline asio::io_context context;

class Client {
private:
	bool connected = false;
	asio::ip::address_v4 ip;
public:
	bool isConnected();
	asio::ip::address_v4 getIp();
};

using Lobby = std::vector<Client>;
inline std::vector<Lobby> lobbies;

void acceptClients();

inline int rng(int min, int max);