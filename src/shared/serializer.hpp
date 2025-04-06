#pragma once

#include "globals.hpp"
#include "packet.hpp"
#include "sizes.h"
#include <cstdint>
#include <istream>
#include <string_view>
#include <cereal/archives/portable_binary.hpp>
#ifdef _MSC_VER
#include <malloc.h>
#endif

//Sort of a wrapper around cereal, but specifically for this project.

std::string serialize(const Packet& data);
Packet deserialize(const std::string& buffer);

//Meant for primitive types, like header_t
template <typename T>
std::string serialize(const T& data);
template <typename T>
T deserialize(const std::string& buffer);