#include "clientBackend.hpp"

asio::ip::address_v4 getServerIp() {
	using namespace asio::ip;

	// Why do we make a local context instead of using the global one?
	// Well, I forgot. Might deprecate it later - to do
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

void forceAvailableName(std::string& name, asio::ip::tcp::socket& s) {
	// Send client name
	comm::send(Packet{ actions::sendName, name }, s);

	// Check whether a client with the same name exists.
	// If true, force user to rechoose a name.
	// The huge logic condition is basically reading a packet as bool.
	// To do (less important): handle exceptions if std::get throws here.
	while (!std::get<bool>(comm::read(mainSocket).parameter)) {
		std::cout << "Ese nombre ya está ocupado. Elija otro: ";
		std::cin >> name;
		comm::send(Packet{ actions::sendName, name }, s);
	}
}

std::vector<cLobby> getLobbies(asio::ip::tcp::socket& s) {
	// Send the action
	comm::send(Packet{ actions::getLobbies, std::monostate{} }, s);
	// Error likely, good for now
	return comm::readParameter<std::vector<cLobby>>(s);
}