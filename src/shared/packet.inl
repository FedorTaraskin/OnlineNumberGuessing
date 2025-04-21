#pragma once
// This file is only meant to be included by packet.hpp
// Do not use it, use packet.hpp

#include <asio.hpp>
#include "serializer.hpp"
#include "ONGconcepts.hpp"

// Overload for types that have .size() (like std::string)
template <validParameter Parameter>
inline header_t Packet<Parameter>::size() const requires hasSizeMFunc<Parameter> {
    return sizeof(action) + parameter.size();
}

// Overload for types that do NOT have .size() (like int32_t, bool)
template <validParameter Parameter>
inline header_t Packet<Parameter>::size() const requires (!hasSizeMFunc<Parameter>) {
    return sizeof(action) + sizeof(parameter);
}

template <validParameter Parameter>
inline void Packet<Parameter>::send(asio::ip::tcp::socket& socket) const {
    // Send the serialized size of the packet
    asio::write(socket, asio::buffer(g_Serialize(this->size())));

    // Send the actual packet
    asio::write(socket, asio::buffer(g_Serialize(*this)));
}