#include "serializer.hpp"

//Returns the serialized data in the form of an STL string.
//WARNING: The string is not actual text, but binary data
std::string serialize(const Packet& data) {
	std::stringstream ss(std::ios::binary);
	{
		cereal::PortableBinaryOutputArchive archive(ss);
		//Calls the `serialize` function inside Packet,
		//storing all of it's contents into ss.
		archive(data); 
	} //Scope for making sure cereal does its job (RAII)
	unsigned int ssSize = ss.tellg();
	#ifdef 
	ss.read(toRet, ssSize);
}

std::string serialize(const T& data) {
	std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
}

Packet deserialize(const std::string& buffer) {
	std::stringstream ss(std::ios::binary);
	//BAD! Will truncate when finds a null char
	ss.write(buffer.data(), buffer.size());
	Packet data;
	{
		cereal::PortableBinaryInputArchive archive(ss);
		archive(data);
	} //Scope for making sure cereal does it's job (RAII)
	return data;
}