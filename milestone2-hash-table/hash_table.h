/**
 * @file hash_table.h
 * @brief This is the header file for HashTable, used in hash_table.cpp
 *
 * @date 09/23/24 - Created by ChatGPT
 * @date 10/17/24 - Modified by jhui
 * @date 01/11/25 - Modified by hhui; 1) added calculateHashCode, 2) modified methods to include hash table size parameter
 * @date 05/31/25 - added additional doxygen style comments
 */

#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "hash_node.h"

 /**
  * @class HashTable
  * @brief Class representing a hash table with chaining for collision handling.
  */
class HashTable {
private:
	/// Array of pointers representing the table buckets
	HashNode** table;

	/// Number of buckets in the hash table
	int numberOfBuckets;

	/// Number of elements currently stored in the table
	int numberOfItems;

public:
	/**
	 * @brief Constructor to initialize the hash table with a given size.
	 * @param hashTableSize The number of buckets to initialize in the hash table.
	 */
	HashTable(int hashTableSize)
		: numberOfBuckets(hashTableSize), numberOfItems(0) {
		table = new HashNode * [hashTableSize];
		for (int i = 0; i < hashTableSize; i++) {
			table[i] = nullptr;
		}
	}

	/**
	 * @brief Gets the internal array of bucket pointers.
	 * @return A pointer to the array of HashNode pointers.
	 */
	HashNode** getTable();

	/**
	 * @brief Gets the number of buckets in the hash table.
	 * @return The number of buckets (table size).
	 */
	int getSize();

	/**
	 * @brief Calculates the hash code for a given key.
	 * @param currentKey The key for which the hash code is to be calculated.
	 * @return The computed hash code (bucket index).
	 */
	int calculateHashCode(int currentKey);

	/**
	 * @brief Checks whether the hash table is empty.
	 * @return True if the table has no entries, false otherwise.
	 */
	bool isEmpty();

	/**
	 * @brief Gets the number of items currently stored in the table.
	 * @return The number of items in the table.
	 */
	int getNumberOfItems();

	/**
	 * @brief Adds a new node to the table.
	 * @param curKey The key associated with the node.
	 * @param myNode Pointer to the node to be added.
	 * @return True if insertion is successful.
	 */
	bool add(int curKey, HashNode* myNode);

	/**
	 * @brief Removes a node with the specified key from the table.
	 * @param curKey The key of the node to remove.
	 * @return True if the node was successfully removed; false if not found.
	 */
	bool remove(int curKey);

	/**
	 * @brief Clears the entire hash table by deleting all entries.
	 */
	void clear();

	/**
	 * @brief Retrieves the node associated with a given key.
	 * @param curKey The key to look up.
	 * @return Pointer to the corresponding HashNode, or nullptr if not found.
	 */
	HashNode* getItem(int curKey);

	/**
	 * @brief Checks if a node with the given key exists in the table.
	 * @param curKey The key to search for.
	 * @return True if the key is found; false otherwise.
	 */
	bool contains(int curKey);

	/**
	 * @brief Prints the contents of the hash table.
	 *
	 * Outputs each bucket and the nodes it contains to both the console
	 * and the output log (via logToFileAndConsole).
	 */
	void printTable();
}; // end class HashTable

#endif
