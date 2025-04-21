#pragma once
#include <asio.hpp>
#include <cstdint> // For size-specific integers
#include "ONGconcepts.hpp"

typedef uint8_t action_t;

// Header size. The header is an unsigned integer
// which says how many bytes are going to be transmitted.
typedef uint16_t header_t;
// 16 bytes gives us message for sending packets with a
// size of 2^16, which is 65'536 bytes, or ~65kb.

namespace actions {
    // Request/answer		  Request	Answer		 Request	 Request	  Request	  Request	 Request	Request
    enum actions : action_t { sendName, approveName, getLobbies, createLobby, closeLobby, joinLobby, startGame, guessNum };
    // Parameters:			  name		unused				     lobbyName,				  lobbyName,			num
    // Parameter types:		  string    bool                     string                   string                int32_t
    // 
    // Note: Where no parameter is, the type will be a bool. Void is not accepted by the compiler :(
}

template <validParameter Parameter>
struct Packet {
    action_t action;
    Parameter parameter;

    inline header_t size() const;

    // Overloads of size(): don't look into it, just use the one above
    inline header_t size() const requires hasSizeMFunc<Parameter>;
    inline header_t size() const requires (!hasSizeMFunc<Parameter>);

    inline void send(asio::ip::tcp::socket& socket) const;

    //Cereal support
    template <class Archive>
    void serialize(Archive& archive) { archive(action, parameter); }
};

#include "packet.inl"