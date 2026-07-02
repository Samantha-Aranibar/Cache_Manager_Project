/**
 * @file hash_table.cpp
 * @brief Implementation of the HashTable class.
 *
 * This file defines the member functions declared in hash_table.h.
 * The HashTable provides constant-time average-case insertion, lookup,
 * and deletion of integer keys using separate chaining with linked lists.
 *
 * It serves as the main indexing structure for the CacheManager class,
 * mapping keys to their associated DLL nodes for O(1) access.
 *
 * @date 10/06/2025 - Initial implementation of constructor, insert, search, and remove.
 * @date 10/07/2025 - Added clear() and loadFromFile() logic.
 * @date 10/08/2025 - Updated documentation and formatting for milestone 3 submission.
 * 
 * @author 
 *  Ayush Rangrej
 *  Samantha Aranibar Valdes
 */

#include <iostream>
using namespace std;
#include "hash_table.h"
#include <fstream>


/**
 * @brief Returns the underlying hash table (vector of bucket pointers).
 * @return Reference to the internal vector of DllNode* buckets.
 */
HashNode** HashTable::getTable() {
    return table;         
}


/**
 * @brief Retrieves the number of buckets in the hash table.
 * @return Integer count of hash table buckets.
 */
int HashTable::getSize() {
    return numberOfBuckets; 
}

/**
 * @brief Checks if the hash table contains no entries.
 * @return true if no nodes exist in any bucket; false otherwise.
 */
bool HashTable::isEmpty() {
    return (numberOfItems == 0);
}

/**
 * @brief Returns the total number of active items in the hash table.
 * @return Integer count of stored nodes.
 */
int HashTable::getNumberOfItems() {
    return numberOfItems;
}

/**
 * @brief Computes a hash code for the specified key.
 * @param key Integer key to hash.
 * @return Integer index (0 ≤ index < table size).
 */
int HashTable::calculateHashCode(int key) {
    int code = key % numberOfBuckets;
    if (code < 0) code += numberOfBuckets;
    return code;
}

/**
 * @brief Inserts a new key into the hash table.
 * @param key Integer key to add.
 * @return Pointer to the created DllNode, or nullptr if the key already exists.
 */
bool HashTable::add(int curKey, HashNode* myNode) {
    int index = calculateHashCode(curKey);
    myNode->next = table[index];
    table[index] = myNode;
    numberOfItems++;
    return true;
}

/**
 * @brief Retrieves a node matching a given key.
 * @param key Integer key to look up.
 * @return Pointer to the matching DllNode, or nullptr if not found.
 */
HashNode* HashTable::getItem(int key) {
    int index = calculateHashCode(key);
    HashNode* num = table[index];
    while (num != nullptr) {
        if (num->key == key) return num; 
        num = num->next;
    }
    return nullptr; 
}

/**
 * @brief Determines whether a key exists in the hash table.
 * @param key Integer key to check.
 * @return true if key exists; false otherwise.
 */
bool HashTable::contains(int key) {
    return (getItem(key) != nullptr); // true if found
}

/**
 * @brief Removes a node with the specified key from the table.
 * @param key Integer key to remove.
 * @return true if removal succeeded; false if the key was not found.
 */
bool HashTable::remove(int curKey) {
    int index = calculateHashCode(curKey);
    HashNode* node = table[index];
    HashNode* prev = nullptr;

    while (node != nullptr) {
        if (node->key == curKey) {
            if (prev) prev->next = node->next;
            else table[index] = node->next;
            delete node;
            numberOfItems--;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

/**
 * @brief Deletes all entries in the hash table.
 *
 * Traverses each bucket, freeing all nodes, and resets
 * the table to an empty state.
 */
void HashTable::clear() {
    for (int i = 0; i < numberOfBuckets; i++) {
        HashNode* student = table[i];
        while (student != nullptr) {
            HashNode* temp = student; // hold node
            student = student->next;  // move next
            delete temp;
        }
        table[i] = nullptr; // reset bucket
    }
    numberOfItems = 0;
}

/**
 * @brief Prints the contents of the hash table to console and output file.
 * logToFileAndConsole(), supporting validation and debugging.
 */
void HashTable::printTable() {
    for (int i = 0; i < numberOfBuckets; i++) {
        std::cout << "Bucket " << i << ": ";
        HashNode* node = table[i];
        while (node) {
            std::cout << "[" << node->key << "]";
            if (node->next) std::cout << " -> ";
            node = node->next;
        }
        std::cout << std::endl;
    }
}
