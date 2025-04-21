#include "clientBackend.hpp"

asio::ip::address_v4 getServerIp() {
	using namespace asio::ip;

	// Why do we make a local context instead of using the global one?
	// Well, I forgot. Might deprecate it later - TODO
	asio::io_context localContext;

	// Make an endpoint representing the server, in UDP-ipv4 mode.
	// Udp because tcp has no broadcast, ipv4 for whole project simplicity.
	udp::endpoint serverEndpoint(udp::v4(), port);

	// Make open socket for server endpoint.
	udp::socket socket(localContext, serverEndpoint);

	std::string buffer;
	// Resize to fit the binary message
	buffer.resize(serializedServerTag.size()); 

	do {
		// Instead of asio::read(), when a socket is UDP you must socket.receive().
		socket.receive_from(asio::buffer(buffer), serverEndpoint);
	// Check that wie received the server tag and not something else
	} while (buffer != serializedServerTag);

	return serverEndpoint.address().to_v4();
};

// TODO
inline std::vector<cLobby> getLobbies() {
	// Send the action
	comm::send(Packet<bool>{actions::getLobbies, NULL}); // TODO

	return comm::read<std::vector<cLobby>>();
}
