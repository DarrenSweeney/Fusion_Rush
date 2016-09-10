#ifndef HASH_H
#define HASH_H

#include <assert.h>

class HashID
{
public:
	HashID(const char* str);

private:
	const static size_t Prime = 0x01000193;		//   16777619
	const static size_t Seed = 0x811C9DC5;		// 2166136261
	size_t hashID;
	size_t HashStringID(const char *str, size_t hash = Seed);
};

#endif