#pragma once
#include <string_view>
#include <string>

class Packet {
public:
    Packet(const char* msg);
    //I am not quite sure about this, a view might be a bad idea.
    //However, copying data an extra time when constructing a packet is slow.
    Packet(std::string_view msg);
    Packet() {};
    std::string data;

    //Cereal support
    template <class Archive>
    void serialize(Archive& archive) { archive(data); }
};