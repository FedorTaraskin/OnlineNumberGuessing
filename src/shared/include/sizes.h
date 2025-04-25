#pragma once

//Can be "decimal" or "binary"
#define sizeScheme decimal

#if sizeScheme == binary
	#define kb *1'024u
	#define mb *1'024*1'024u
	#define gb *1'024*1'024*1'024u
#elif sizeScheme == decimal
	#define kb *1'000u
	#define mb *1'000'000u
	#define gb *1'000'000'000u
#else
	#error Incorrect counting scheme in __FILE__
#endif