#pragma once
//The the first 4 bytes of any transmitted data is a uint32_t
//value representing the complete size of that transmission.

//IPV4 adresses can be max 15 chars long
//+1 for the null termination
#define maxIpv4StringSize 15 + 1

inline unsigned int headerSize = 4;
//We utilize exclusively ipv4 in this project.

//To be initialized by frontend
inline unsigned int maxTries; 
inline signed int min, max; //Range of possible number

#include <asio.hpp>
inline asio::io_context context;