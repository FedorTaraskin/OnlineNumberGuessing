//A header file that includes all the functionality in the "server" folder.
//There is also a "serverFrontend.cpp" file in this directory: it is an example use case of this.
#include "serverGlobals.hpp"
#include <vector>
#include "asio.hpp"
#include <thread>
#include "globals.hpp"

//For the sake of simplicity and getting this program done before the end of the year,
//we use syncronous i/o with threads. Fine for a few clients, horrible for many.

inline asio::io_context context;

class Client {
private:
	bool connected = false;
	asio::ip::address_v4 ip;
public:
	bool isConnected();
	asio::ip::address_v4 getIp();
};

//I do not understand why, but w/o 'inline', this makes linker errors
using Lobby = std::vector<Client>;
inline std::vector<Lobby> lobbies;

void acceptClients();
