#include "clientBackend.hpp"

asio::ip::address_v4 getServerIp() {
	using namespace asio::ip;
	asio::io_context localContext;
	udp::endpoint serverEndpoint(udp::v4(), port);

	//Make socket
	udp::socket socket(localContext, udp::endpoint(udp::v4(), port));

	#ifdef _DEBUG
	(socket.is_open()) ? std::clog << "Open\n" : std::clog << "Closed\n";
	#endif

	std::string buffer;
	//Instead of asio::read(), when a socket is UDP you must socket.receive().
	socket.receive(asio::buffer(buffer)); //TODO
	if (deserialize<std::string>(buffer) != serverTag) {
		std::clog << deserialize<std::string>(buffer) << '\n';
		throw std::runtime_error("Trash found, expected server tag.");
	}
	
	return serverEndpoint.address().to_v4();
}