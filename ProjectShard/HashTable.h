#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "HashID.h"
#include <string>
#include <iostream>

// TODO(Darren): Implement template here and compare with 
// std_underorded map and it's constructor.

class HashTable
{
public:
	HashTable();
	~HashTable();

	unsigned int HashIndex(HashID hashID);
	void Insert(HashID hashID, std::string drink);
	std::string Find(HashID hashID);
	void Remove(HashID hashID);
	// Calculate the number of items in list giving at a index.
	unsigned int SizeOfBucket(int index);
	void PrintTable();
	void PrintTableBuckets(int index);

private:
	static const unsigned int TABLE_SIZE = 4;

	struct Item
	{
		HashID hashID;
		std::string drink;
		Item *next;
	};

	Item* hashTable[TABLE_SIZE];
};

#endif