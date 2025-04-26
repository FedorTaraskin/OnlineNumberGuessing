#pragma once
#include "ONGconcepts.hpp"
#include <asio/ip/tcp.hpp>
#include <cstdint> // For size-specific integers

typedef uint8_t action_t;

// Header size. The header is an unsigned integer
// which says how many bytes are going to be transmitted.
typedef uint16_t header_t;
// 16 bytes gives us message for sending packets with a
// size of 2^16, which is 65'536 bytes, or ~65kb.

namespace actions {
    // Request/answer		  Request	Answer		 Both   	 Request	  Request	  Request	 Request	Request
    enum actions : action_t { sendName, approveName, getLobbies, createLobby, closeLobby, joinLobby, startGame, guessNum };
    // Parameters:			  name		unused		 *readbelow  lobbyName,				  lobbyName,			num
    // Parameter types:		  string    bool         *readbelow  string                   string                int32_t
    // 
    // *getLobbies: When sent from client to server, has no parameter type. When sent from server to client,
    // the parameter type is vector<cLobby>.
}

template <validParameter Parameter>
struct Packet {
    action_t action;
    Parameter parameter;

    // Returns the size of the parameter. 
    // Action size is not included!
    inline header_t size() const;

    // Overloads of size(): don't look into it, just use the one above
    inline header_t size() const requires hasSizeMFunc<Parameter>;
    inline header_t size() const requires (!hasSizeMFunc<Parameter>);

    inline void send(asio::ip::tcp::socket& socket) const;

    //Cereal support
    template <class Archive>
    void serialize(Archive& archive) { archive(action, parameter); }
};

// Specialized overload of Packet struct for no parameter.
template <>
struct Packet<void> {
    action_t action;

    inline header_t size() const;

    inline void send(asio::ip::tcp::socket& socket) const;

    //Cereal support
    template <class Archive>
    void serialize(Archive& archive) { archive(action); }
};

#include "packet.inl"