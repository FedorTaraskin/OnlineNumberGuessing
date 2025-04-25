#include <chrono>
#include <cstdint>
#include <iostream>
using namespace std::chrono;

int main() {
	std::chrono::high_resolution_clock::time_point start, fastu8, uint, fastu32, u32, u8;
	for (unsigned int loops = 0; loops < 6; loops++) {
		start = std::chrono::high_resolution_clock::now();
		for (uint_fast32_t i = 0; i < UINT_FAST8_MAX; i++) {}
		fastu8 = high_resolution_clock::now();
	}
	std::cout << std::chrono::duration_cast<nanoseconds>(fastu8 - start) << '\n';
}

// u8: 900-1000 in debug, 0-100 in release
// u32: 700-800 in debug, 0-100 in release