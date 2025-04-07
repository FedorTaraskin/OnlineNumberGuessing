#include "packet.hpp"

Packet::Packet(std::string_view msg) {
    data = std::string(msg);
}

Packet::Packet(const char* msg) {
    data = std::string(msg);
}