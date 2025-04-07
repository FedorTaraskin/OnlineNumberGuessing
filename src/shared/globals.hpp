#pragma once
#include <cstdint> //For size-specific integers

const inline uint16_t port = 9999u;

//Header size. The header is an unsigned integer
//which says how many bytes are going to be transmitted.
typedef uint16_t header_t;
//16 bytes gives us message for sending packets with a
//size of 2^16, which is 65'536 bytes, or ~65kb.
// 
//How big header_t becomes after serialization.
const inline unsigned int headerRawSize = 3; 

typedef uint8_t byte;