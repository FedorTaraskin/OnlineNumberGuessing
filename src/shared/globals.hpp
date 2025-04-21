#pragma once
#include <string>
#include <asio.hpp>
#include <thread>
#include "comm.hpp"

// To be used by every main function as a return value.
// This way, we can set this variable to true if something goes wrong,
// reporting the failure to the OS
inline int mainReturnCode = 0;

inline const uint8_t maxClientNameSize = 30;