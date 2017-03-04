#ifndef HASH_H
#define HASH_H

#include <assert.h>

class HashID
{
public:
	HashID();
	HashID(const char* str);
	const unsigned long GetValue() const;
	bool operator==(const HashID hashID);

	unsigned long hashID;

private:
	// Values based on http://isthe.com/chongo/tech/comp/fnv/
	const static unsigned long FNV_prime		=	0x01000193;	// 0016777619
	const static unsigned long FNV_offset_basis =	0x811C9DC5;	// 2166136261

	unsigned long HashStringID(const char *str);
};

#define SID(str) HashID(str)

#endif