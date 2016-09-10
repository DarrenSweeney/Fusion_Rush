#include "HashID.h"

HashID::HashID(const char* str)
	: hashID(HashStringID(str))
{

}

// Values based on http://isthe.com/chongo/tech/comp/fnv/
size_t HashID::HashStringID(const char *str, size_t hash)
{
	assert(str);

	const unsigned char *ptr = (const unsigned char*)str;

	while (*ptr)
	{
		hashID = (*ptr++ ^ hash) * Prime;
	}

	return hashID;
}

#define SID(str) HashID(str)