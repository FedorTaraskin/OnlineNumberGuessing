#pragma once
#include <cstdint> //For size-specific integers
#include <string>

const inline uint16_t port = 9876;

//Header size. The header is an unsigned integer
//which says how many bytes are going to be transmitted.
typedef uint16_t header_t;
//16 bytes gives us message for sending packets with a
//size of 2^16, which is 65'536 bytes, or ~65kb.

//How big header_t becomes after serialization.
const inline unsigned int headerRawSize = 3; 

typedef uint8_t byte;

enum actions : uint8_t {
	createLobby, closeLobby, joinLobby, startGame, guessNum
};

#include "serializer.hpp"
const inline std::string serverTag = "ONGserT";
const inline std::string serializedServerTag = serialize<std::string>(serverTag);