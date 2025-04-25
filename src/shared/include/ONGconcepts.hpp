#pragma once
#include "globals.hpp"
#include <concepts>
#include <cstdint>
#include <string>
#include <vector>

// This file contains concepts that are used throughout the whole
// codebase. Concepts are a relatively new C++20 feature used to
// constrain templated functions and classes, so that they can
// only be used with a specified range of types.

// https://youtu.be/jzwqTi7n-rg?feature=shared&t=80

// https://youtu.be/FRkJCvHWdwQ?feature=shared&t=1140

template <typename T>
concept hasSizeMFunc = requires (T x) { x.size(); };

// Constraints types to only those allowed by a packet's parameter.
// Allowed: bool, string, int32_t, vector<cLobby>

template <typename Parameter>
concept validParameter =
	std::same_as <Parameter, bool> ||
	std::same_as <Parameter, std::string> ||
	std::same_as <Parameter, int32_t> ||
	std::same_as <Parameter, std::vector<cLobby>>;