#pragma once
#include <string>
#include <asio.hpp>
#include <thread>
#include <cstdint>

typedef uint8_t action_t;

// Header size. The header is an unsigned integer
// which says how many bytes are going to be transmitted.
typedef uint16_t header_t;
// 16 bytes gives us message for sending packets with a
// size of 2^16, which is 65'536 bytes, or ~65kb.

// To be used by every main function as a return value.
// This way, we can set this variable to true if something goes wrong,
// reporting the failure to the OS
inline int mainReturnCode = 0;

inline const uint8_t maxClientNameSize = 30;

// This "Lobby" struct is different from a server's Lobby struct.
// The server additionally stores IPs, threads and sockets for each client.
struct cLobby {
	std::string name;
	std::vector<std::string> clients;

	// Cereal support
	template <typename Archive>
	void serialize(Archive& ar) { ar(name, clients); }
};