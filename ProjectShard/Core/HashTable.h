#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "HashID.h"
#include <iostream>

template <class T>
class HashTable
{
public:
	HashTable();
	~HashTable();

	unsigned int HashIndex(HashID hashID);
	void Insert(HashID hashID, T value);
	T* Find(HashID hashID);
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
		T value;
		Item *next;
	};

	Item* hashTable[TABLE_SIZE];
};


template <class T>
HashTable<T>::HashTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		hashTable[i] = new Item;
		hashTable[i]->hashID.hashID = 0x00000000;
		//hashTable[i]->value = 0;
		hashTable[i]->next = NULL;
	}
}

template <class T>
HashTable<T>::~HashTable()
{
	Item *ptr = NULL;
	Item *curr;
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		ptr = hashTable[i];
		if (ptr == NULL)
			continue;

		while (ptr->next != NULL)
		{
			curr = ptr;
			ptr = ptr->next;
			delete curr;
		}
	}
}

template <class T>
unsigned int HashTable<T>::HashIndex(HashID hashID)
{
	int index = hashID.hashID % TABLE_SIZE;

	return index;
}

template <class T>
void HashTable<T>::Insert(HashID hashID, T value)
{
	int index = HashIndex(hashID);

	if (hashTable[index]->hashID.GetValue() == 0x00000000)
	{
		hashTable[index]->hashID = hashID;
		hashTable[index]->value = value;
	}
	else
	{
		Item *ptr = hashTable[index];
		Item *n = new Item;
		n->hashID = hashID;
		n->value = value;
		n->next = NULL;

		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}

template <class T>
T* HashTable<T>::Find(HashID hashID)
{
	int index = HashIndex(hashID);
	T *value = new T;

	Item *ptr = hashTable[index];
	while (ptr != NULL)
	{
		if (ptr->hashID.hashID == hashID.hashID)
		{
			*value = ptr->value;
		}
		ptr = ptr->next;
	}

	return value;
}

template <class T>
void HashTable<T>::Remove(HashID hashID)
{
	int index = HashIndex(hashID);

	Item *ptr = hashTable[index];

	if (!ptr)
	{
		std::cout << "There is no matching hash value to remove." << std::endl;
		return;
	}

	if (ptr->hashID == hashID && ptr->next == NULL)
	{
		std::cout << hashID.GetValue() << " hash ID removed" << std::endl;
		delete ptr;
	}

	Item *currentNode;

	while (ptr->next != NULL)
	{
		currentNode = ptr;
		ptr = ptr->next;
		if (ptr->hashID == hashID)
		{
			currentNode->next = ptr->next;
			std::cout << hashID.GetValue() << " hash ID removed" << std::endl;
			delete ptr;
		}
	}
}

template <class T>
unsigned int HashTable<T>::SizeOfBucket(int index)
{
	int count = 0;

	if (hashTable[index]->hashID.GetValue() == 0x00000000)
	{
		return count;
	}
	else
	{
		count++;
		Item* ptr = hashTable[index];
		while (ptr->next != NULL)
		{
			count++;
			ptr = ptr->next;
		}
	}

	return count;
}

template <class T>
void HashTable<T>::PrintTable()
{
	int number;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		number = SizeOfBucket(i);

		std::cout << "-----------------------\n" << std::endl;
		std::cout << "Index: " << i << std::endl;
		std::cout << "Hash ID: " << hashTable[i]->hashID.hashID << std::endl;
		std::cout << "Hash Value: " << hashTable[i]->value << std::endl;
		std::cout << "# of items = " << number << std::endl;
		std::cout << "-----------------------\n" << std::endl;
	}
}

template <class T>
void HashTable<T>::PrintTableBuckets(int index)
{
	Item *ptr = hashTable[index];

	if (ptr->hashID.hashID == 0)
		std::cout << "Index = " << index << " is empty" << std::endl;
	else
	{
		std::cout << "Index " << index << " contains the following item\n" << std::endl;

		while (ptr != NULL)
		{
			std::cout << "-----------------------\n" << std::endl;
			std::cout << "Hash ID : " << ptr->hashID.hashID << std::endl;
			std::cout << "Hash Value: " << ptr->value << std::endl;
			std::cout << "-----------------------\n" << std::endl;
			ptr = ptr->next;
		}
	}
}

#endif