//"Main" server file
#include <iostream>
#include "asio.hpp"
#include "serverBackend.hpp"
#include <string>

#include <thread>

#define _CRT_SECURE_NO_WARNINGS //Shut up, MSVC
#include <cstring>
#include <iostream>

int main() {
	while (true) {
		try {
			announce::start();
			acceptClients();
		}
		catch (std::exception& e) {
			std::cerr << e.what();
			return -1;
		}
	}
	announce::stop();
}