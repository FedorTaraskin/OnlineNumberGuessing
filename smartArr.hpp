#pragma once
#include <malloc.h>
//This is not here to replace std::array.
//Instead, this allows one to make x-sized arrays at runtime, on the stack.

template <typename T, size_t size>
struct fastArr {
	T* data;

};