#pragma once
#include "globals.hpp"
#include <string_view>

class Packet {
private:
    header_t totalSize = 0;
public:
    Packet(const char* msg);
    Packet(std::string_view msg);
    Packet() {};
    header_t header(); //The packet header consists of it's size
    std::string_view data;

    //Cereal support
    template <class Archive>
    void serialize(Archive& archive);
};