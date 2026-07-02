/**
 * @file cache_manager.cpp
 * @brief Implementation of the CacheManager class.
 *
 * This file defines the member functions declared in cache_manager.h.
 * The CacheManager provides FIFO-based cache replacement behavior using
 * a combination of a HashTable (for O(1) lookups) and a DoublyLinkedList
 * (for maintaining insertion order).
 *
 * Each cache operation (add, remove, clear, contains, etc.) is logged using
 * logToFileAndConsole() for detailed runtime tracing.
 *
 * @date 10/09/2025 - Initial version with basic caching functionality.
 * @date 10/10/2025 - Integrated with DoublyLinkedList and HashTable modules.
 * @date 10/11/2025 - Finalized and documented for Milestone 3 submission.
 * @authors
 *  Samantha Aranibar Valdes
 *  Ayush Rangrej
 */

#include <iostream>
#include <string>
using namespace std;
#include "cache_manager.h"

// External log function
extern void logToFileAndConsole(std::string msg);

/**
 * @brief Returns a pointer to the internal hash table.
 * @return Pointer to the HashTable object.
 */
HashTable* CacheManager::getTable() {
    return hashTable;
}

/**
 * @brief Returns a pointer to the internal FIFO list.
 * @return Pointer to the DoublyLinkedList object.
 */
DoublyLinkedList* CacheManager::getList() {
    return doublyLinkedList;
}

/**
 * @brief Gets the current number of items in the cache.
 * @return Number of items in the cache.
 */
int CacheManager::getSize() {
    return doublyLinkedList->getSize();
}

/**
 * @brief Checks whether the cache is empty.
 * @return True if the cache has no entries, false otherwise.
 */
bool CacheManager::isEmpty() {
    return hashTable->isEmpty();
}

/**
 * @brief Adds a node to the cache.
 * @param curKey Key associated with the node.
 * @param myNode Pointer to the node to be added.
 * @return True if the operation succeeds, false otherwise.
 */
bool CacheManager::add(int curKey, DllNode* myNode) {
    if (!myNode) return false;
    if (getSize() >= maxCacheSize) {
        int oldestKey = doublyLinkedList->head->key;
        remove(oldestKey);
        logToFileAndConsole("Cache full - oldest entry evicted (Key: " + std::to_string(oldestKey) + ")");
    }
    HashNode* newHashNode = new HashNode(curKey, myNode);
    hashTable->add(curKey, newHashNode);
    doublyLinkedList->insertAtTail(curKey, myNode);
    return true;
}

/**
 * @brief Removes a node from the cache based on the key.
 * @param curKey Key of the node to be removed.
 * @return True if the operation succeeds, false otherwise.
 */
bool CacheManager::remove(int curKey) {
    if (!contains(curKey)) return false;

    // Remove from both structures
    hashTable->remove(curKey);
    doublyLinkedList->remove(curKey);
    logToFileAndConsole("Removed entry (Key: " + std::to_string(curKey) + ")");
    return true;
}

/**
 * @brief Clears all entries from the cache.
 */
void CacheManager::clear() {
    hashTable->clear();
    doublyLinkedList->clear();
}

/**
 * @brief Retrieves a node from the cache.
 * @param curKey Key of the node to retrieve.
 * @return Pointer to the DllNode if found, nullptr otherwise.
 */
DllNode* CacheManager::getItem(int curKey) {
    HashNode* temp = hashTable->getItem(curKey);
    if (!temp) return nullptr;
    return temp->fifoNode; 
}

/**
 * @brief Gets the maximum cache size.
 * @return Maximum number of entries the cache can hold.
 */
int CacheManager::getMaxCacheSize() {
    return maxCacheSize;
}

/**
 * @brief Checks if a specific key exists in the cache.
 * @param curKey Key to check.
 * @return True if the key exists in the cache, false otherwise.
 */
bool CacheManager::contains(int curKey) {
    return hashTable->contains(curKey);
}

/**
 * @brief Prints the current contents of the cache to console and output file.
 */
void CacheManager::printCache() {
    cout << "---- CACHE CONTENTS ----" << endl;
    cout << "Here are the FIFO List contents:" << endl;

    DllNode* curr = doublyLinkedList->tail;
    while (curr != nullptr) {
        cout << "FIFO Node key: " << curr->key << endl;
        curr = curr->prev;
    }
    cout << "End of FIFO List" << endl << endl;

    cout << "Here are the Hash Table contents (" << hashTable->getNumberOfItems() << " entries):" << endl;
    hashTable->printTable();
    cout << "End of table" << endl << endl;

    cout << "End of cache contents" << endl;
    cout << "------------------------" << endl;
}
