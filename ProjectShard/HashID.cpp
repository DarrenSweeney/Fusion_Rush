#include "HashID.h"

HashID::HashID() { }

HashID::HashID(const char* str)
	: hashID(HashStringID(str)) { }

const unsigned long HashID::GetValue() const
{
	return hashID;
}

// Hash a C-style string using fnv-1a
unsigned long HashID::HashStringID(const char *str)
{
	assert(str);

	hashID = FNV_offset_basis;
	while (*str)
	{
		hashID = (hashID ^ *str++) * FNV_prime;
	}

	return hashID;
}

bool HashID::operator==(const HashID hashID)
{
	return this->hashID == hashID.GetValue();
}