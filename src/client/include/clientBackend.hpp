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

// Forces the client to choose an available name.
void forceAvailableName(std::string& name, asio::ip::tcp::socket& s);

inline std::vector<cLobby> getLobbies();

inline asio::ip::tcp::socket mainSocket{ comm::context, asio::ip::tcp::v4() };