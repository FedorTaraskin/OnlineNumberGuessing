#pragma once

#include <asio.hpp>
#include <vector>
#include "globals.hpp"
#include "serializer.hpp"

//Temp
#include <iostream>
#include <stdexcept>

asio::ip::address_v4 getServerIp();

inline asio::io_context context;
inline asio::ip::tcp::socket mainSocket(context);

inline std::vector<Lobby> getLobbies();