#pragma once
// Sort of a wrapper around cereal, but specifically for this project.

#include <string>

// Returns the serialized data in the form of an STL string.
// WARNING: The string is not actual text, but binary data

template <typename T>
// The g_ means global. It is here to separate it from the "serialize()"
// function, which is used by cereal in it's internals.
inline std::string g_Serialize(const T& data);
template <typename T>
inline T g_Deserialize(const std::string_view buffer);

// This is kind of fucked up, but...
// Templates don't really allow me to do this correctly.
// Sooo, yikes!
// (If attempted the correct way, linker errors arise.)

// The actual code
#include "serializer.cpp"