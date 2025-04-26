#pragma once
#include "ONGconcepts.hpp"
#include "packet.hpp"
#include "serializer.hpp"
#include <asio.hpp>
#include <cstdint>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

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

// How big action_t becomes when serialized
const inline uint_fast8_t serializedActionSize = g_Serialize((action_t)0).size();

namespace comm {
    inline asio::io_context context;

    // Send function
    template <validParameter Parameter>
    inline void send(const Packet<Parameter> &data, asio::ip::tcp::socket& localSock);

    // Read function
    template <validParameter Parameter>
    inline Packet<Parameter> read(asio::ip::tcp::socket& localSock);
}

// Include definitions at the end of the header
#include "comm.inl"