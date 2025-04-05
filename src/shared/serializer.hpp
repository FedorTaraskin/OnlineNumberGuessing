#pragma once

#include "globals.hpp"
#include "packet.hpp"
#include <cstdint>
#include <istream>
#include <string_view>
#include <cereal/archives/portable_binary.hpp>

std::string serialize(const Packet& data);
template <typename T>
std::string serialize(const T& data);

Packet deserialize(const std::string& buffer);