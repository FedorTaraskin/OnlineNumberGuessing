//"Main" server file
#include "globals.hpp"
#include "serverBackend.hpp"
#include <iostream>

int main() {
	std::clog << "Starting server...\n";
	announce::start();
	while (true) {
		try {
			acceptClients();
		}
		catch (std::exception& e) {
			std::cerr << e.what();
			mainReturnCode = -1;
		}
	}
	announce::stop();
	return mainReturnCode;
}