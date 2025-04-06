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
	//Attempt to reduce heap allocs
	char* serializedData;
	#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__) || defined(_MSC_VER)
	if (ssSize < 256 kb) {
		//Compiler-specific stack allocations
		#ifdef _MSC_VER
		serializedData = (char*)_alloca(ssSize * sizeof(char));
		#elif defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
		char serializedData[ssSize];
		#endif
	}
	else serializedData = new char[ssSize];
	#else
	serializedData = new char[ssSize];
	#endif
	ss.read(serializedData, ssSize);
	//return std::string(serializedData, ssSize);
	return std::string(ss.view());
}

//Meant for primitive types, like header_t
template <typename T>
std::string serialize(const T& data) { //TODO
	std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
	ss.write()
}

Packet deserialize(const std::string& buffer) {
	std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
	//BAD! Will truncate when finds a null char
	//Or will it?
	ss.write(buffer.data(), buffer.size());
	Packet data;
	{
		cereal::PortableBinaryInputArchive archive(ss);
		archive(data);
	} //Scope for making sure cereal does it's job (RAII)
	return data;
}

template <typename T>
T deserialize(const std::string& buffer) { //TODO

}