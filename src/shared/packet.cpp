#include "packet.hpp"

Packet::Packet(std::string_view msg) {
    data = msg;
}

Packet::Packet(const char* msg) {
    data = msg;
}

header_t Packet::header() {
    if (!totalSize) return totalSize = data.size() + sizeof(header_t);
}