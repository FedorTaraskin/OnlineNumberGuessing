#include "serializer.hpp"

//Returns the serialized data in the form of an STL string.
//WARNING: The string is not actual text, but binary data
std::string serialize(const Packet& data) {
	std::ostringstream ss(std::ios::binary);
	{
		cereal::PortableBinaryOutputArchive archive(ss);
		//Calls the `serialize` function inside Packet,
		//storing all of it's contents into ss.
		archive(data); 
	} //Scope for making sure cereal does its job (RAII)
	return ss.str();
}

Packet deserialize(const std::string& buffer) {
	std::stringstream ss(std::ios::binary);
	ss << buffer;
	Packet data;
	{
		cereal::PortableBinaryInputArchive archive(ss);
		archive(data);
	} //Scope for making sure cereal does it's job (RAII)
	return data;
}