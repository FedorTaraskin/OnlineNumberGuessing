#include "packet.hpp"

template <typename Parameter>
header_t Packet<Parameter>::size() {
	return sizeof(action) + std::size(parameter);
}

template <typename Parameter>
void Packet<Parameter>::send(asio::ip::tcp::socket & socket) {
	// Send the serialized size of the packet
	asio::write(socket, asio::buffer(serialize(static_cast<header_t>(this.size()))));

	// Send the actual packet
	asio::write(socket, asio::buffer(serialize(this)));
}