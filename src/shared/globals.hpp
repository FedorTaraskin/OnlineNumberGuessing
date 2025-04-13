#pragma once
#include <cstdint> // For size-specific integers
#include <string>
#include <asio.hpp>

const inline uint16_t port = 9876;

// Header size. The header is an unsigned integer
// which says how many bytes are going to be transmitted.
typedef uint16_t header_t;
// 16 bytes gives us message for sending packets with a
// size of 2^16, which is 65'536 bytes, or ~65kb.

// How big header_t becomes after serialization.
const inline unsigned int headerRawSize = 3; 

//typedef uint8_t byte; // Deprecated

typedef uint8_t action_t;

namespace actions {
	enum actions : action_t { sendName,		getLobbies, createLobby, closeLobby, joinLobby, startGame, guessNum };
	// Parameters:			  name			lobbyName,				 lobbyName,						   num
	// Parameter types:		  std::string	std::string				 std::string					   int32_t
}

#include "serializer.hpp"
const inline std::string serverTag = "ONGserT";
const inline std::string serializedServerTag = serialize<std::string>(serverTag);

// To be used by every main function as a return value.
// This way, we can set this variable to true if something goes wrong,
// reporting the failure to the OS
inline int mainReturnCode = 0;

struct Client {
	std::string name;
	asio::ip::address_v4 ip;
	Client() = default;
	Client(asio::ip::address_v4 ipToSet, std::string_view nameToSet)
		: ip(ipToSet), name(nameToSet) {
	}
};

struct Lobby {
	std::vector<Client> players;
	std::string name;
};