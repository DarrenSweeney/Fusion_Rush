#include "HashID.h"

HashID::HashID(const char* str)
	: hashID(HashStringID(str)) { }

// Hash a C-style string using fnv1-a
unsigned long HashID::HashStringID(const char *str, unsigned long hash)
{
	assert(str);

	const unsigned char *ptr = (const unsigned char*)str;

	while (*ptr)
	{
		hashID = (*ptr++ ^ hash) * Prime;
	}

	return hashID;
}