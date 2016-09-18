#include "HashID.h"

HashID::HashID() { }

HashID::HashID(const char* str)
	: hashID(HashStringID(str)) { }

const unsigned long HashID::GetValue() const
{
	return hashID;
}

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

bool HashID::operator==(const HashID hashID)
{
	return this->hashID == hashID.GetValue();
}