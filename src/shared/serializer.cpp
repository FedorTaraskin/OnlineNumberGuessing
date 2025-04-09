//#include "serializer.hpp"
#include "globals.hpp"
#include "packet.hpp"
#include "sizes.h"
#include <cstdint>
#include <istream>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>
//Returns the serialized data in the form of an STL string.
//WARNING: The string is not actual text, but binary data
template <typename T>
inline std::string serialize(const T& data) {
	std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
	{
		cereal::PortableBinaryOutputArchive archive(ss);
		archive(data);
	} //Scope for making sure cereal does its job (RAII)
	return std::string(ss.view());
}

template <typename T>
inline T deserialize(const std::string& buffer) {
	std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
	ss.write(buffer.data(), buffer.size());
	T data;
	{
		cereal::PortableBinaryInputArchive archive(ss);
		archive(data);
	} //Scope for making sure cereal does it's job (RAII)
	return data;
}