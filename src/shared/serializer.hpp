#pragma once
//Sort of a wrapper around cereal, but specifically for this project.

#include <string>

//Returns the serialized data in the form of an STL string.
//WARNING: The string is not actual text, but binary data
template <typename T>
inline std::string serialize(const T& data);
template <typename T>
inline T deserialize(const std::string& buffer);

//This is kind of fucked up, but...
//Templates don't really allow me to do this correctly.
//Sooo, yikes!
//(If attempted the correct way, linker errors arise.)

//The actual code
#include "serializer.cpp"