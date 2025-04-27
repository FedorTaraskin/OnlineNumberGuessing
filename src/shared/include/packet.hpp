#pragma once
#include "globals.hpp"
#include <asio.hpp>
#include <string>
#include <variant>
#include <vector>

namespace actions {
    // Request/answer		  Request	Answer		 Both   	 Request	  Request	  Request	 Request	Request
    enum actions : action_t { sendName, approveName, getLobbies, createLobby, closeLobby, joinLobby, startGame, guessNum };
    // Parameters:			  name		unused		 *readbelow  lobbyName,				  lobbyName,			num
    // Parameter types:		  string    bool         *readbelow  string                   string                int32_t
    // 
    // *getLobbies: When sent from client to server, has no parameter type. When sent from server to client,
    // the parameter type is vector<cLobby>.
}

typedef std::variant<std::monostate, std::string, bool, int32_t, std::vector<cLobby>> Parameter_t;

struct Packet {
    action_t action;
    Parameter_t parameter;

    inline void send(asio::ip::tcp::socket& socket) const noexcept;

    //Cereal support
    template <class Archive>
    void serialize(Archive& archive) { archive(action, parameter); }
};