#pragma once
// This file is only meant to be included by packet.hpp
// Do not use it, use packet.hpp
#include "ONGconcepts.hpp"
#include <asio.hpp>
#include "serializer.hpp"

inline void Packet::send(asio::ip::tcp::socket& socket) const noexcept {
    // Send the serialized size of the packet
    asio::write(socket, asio::buffer(g_Serialize(serializedSize())));

    // Send the actual packet
    asio::write(socket, asio::buffer(g_Serialize(*this)));
}

inline header_t serializedSize() {
    if (!m_serializedSize) m_serializedSize = g_Serialize()
}