#include "HashTable.h"

HashTable::HashTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		hashTable[i] = new Item;
		hashTable[i]->hashID.hashID = 0x00000000;
		hashTable[i]->drink = "";
		hashTable[i]->next = NULL;	
	}
}

HashTable::~HashTable()
{
	Item *ptr = NULL;
	Item *curr;
	for (int i = 0; i < TABLE_SIZE; ++i) {
		ptr = hashTable[i];
		if (ptr == NULL)
			continue;

		while (ptr->next != NULL) {
			curr = ptr;
			ptr = ptr->next;
			delete curr;
		}
	}
}

unsigned int HashTable::HashIndex(HashID hashID)
{
	int index = hashID.hashID % TABLE_SIZE;

	return index;
}

void HashTable::Insert(HashID hashID, std::string drink)
{
	int index = HashIndex(hashID);

	if (hashTable[index]->hashID.GetValue() == 0x00000000)
	{
		hashTable[index]->hashID = hashID;
		hashTable[index]->drink = drink;
	}
	else
	{
		Item *ptr = hashTable[index];
		Item *n = new Item;
		n->hashID = hashID;
		n->drink = drink;
		n->next = NULL;

		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}

std::string HashTable::Find(HashID hashID)
{
	int index = HashIndex(hashID);
	std::string drink = "";

	Item *ptr = hashTable[index];
	while (ptr != NULL)
	{
		if (ptr->hashID.hashID == hashID.hashID)
		{
			drink = ptr->drink;
		}
		ptr = ptr->next;
	}

	return drink;
}

void HashTable::Remove(HashID hashID)
{
	int index = HashIndex(hashID);

	Item *ptr = hashTable[index];

	if (!ptr)
	{
		std::cout << "There is no mathcing hash value to remove." << std::endl;
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

unsigned int HashTable::SizeOfBucket(int index)
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

void HashTable::PrintTable()
{
	int number;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		number = SizeOfBucket(i);

		std::cout << "-----------------------\n" << std::endl;
		std::cout << "Index: " << i << std::endl;
		std::cout << "Hash Value: " << hashTable[i]->hashID.hashID << std::endl;
		std::cout << "Drink Value: " << hashTable[i]->drink << std::endl;
		std::cout << "# of items = " << number << std::endl;
		std::cout << "-----------------------\n" << std::endl;
	}
}

void HashTable::PrintTableBuckets(int index)
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
			std::cout << "Hash Value : " << ptr->hashID.hashID << std::endl;
			std::cout << "Drink Value: " << ptr->drink << std::endl;
			std::cout << "-----------------------\n" << std::endl;
			ptr = ptr->next;
		}
	}
}