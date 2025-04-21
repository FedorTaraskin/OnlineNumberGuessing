#pragma once
#include <asio.hpp>
#include "packet.hpp"
#include "ONGconcepts.hpp"
#include "serializer.hpp"
//#include "globals.hpp"

// For the sake of simplicity and getting this program done before the end of the year,
// we use syncronous i/o with threads. Fine for a few clients, horrible for many.
// We utilize exclusively ipv4 in this project.
// UDP for broadcasting (server discovery), TCP for everything else.

const inline uint16_t port = 9876;

// How big header_t becomes after serialization.
const inline unsigned int headerRawSize = 3;

// Tag to identify servers. Used for automatic server discovery from clients on LAN
const inline std::string serverTag = "ONGserT";
const inline std::string serializedServerTag = g_Serialize<std::string>(serverTag);
// todo: make the above two lines ^^^ be processed at compile-time

namespace comm {
    inline asio::io_context context;
    inline asio::ip::tcp::socket mainSocket{ context, asio::ip::tcp::v4() };

    // Declarations
    inline void send(const hasSizeMFunc auto& data);
    template <typename Parameter>
    inline Packet<Parameter> read(asio::ip::tcp::socket localSock = mainSocket);
}

// Include definitions at the end of the header
#include "comm.inl"