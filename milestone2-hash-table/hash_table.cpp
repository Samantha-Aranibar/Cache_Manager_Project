/**
 * @file hash_table.cpp
 * @brief Implementation file for the HashTable class.
 * 
 * @author Samantha Aranibar
 */

#include "hash_table.h"
#include <iostream>

/**
 * @brief Gets the internal hash table array.
 * @return Pointer to the array of HashNode pointers representing the table.
 */
HashNode** HashTable::getTable() {
    return table;
}

/**
 * Gets the number of buckets in the hash table.
 * @return The size of the hash table (number of buckets).
 */
int HashTable::getSize() {
    return numberOfBuckets;
}

/**
 * Calculates the hash code for a given key using modulo division.
 * @param currentKey The key to hash.
 * @return The computed bucket index 
 */
int HashTable::calculateHashCode(int currentKey) {
    return currentKey % numberOfBuckets;
}

/**
 * @brief Checks if the hash table is empty.
 * @return True if there are no items in the table, false otherwise.
 */
bool HashTable::isEmpty() {
    return numberOfItems == 0;
}

/**
 * @brief Gets the current number of items stored in the hash table.
 * @return The count of items in the table.
 */
int HashTable::getNumberOfItems() {
    return numberOfItems;
}

/**
 * @brief Adds a new node to the hash table using chaining for collision resolution.
 * @param curKey The key of the node to add.
 * @param myNode Pointer to the HashNode to be inserted.
 * @return True if the node was successfully added.
 */
bool HashTable::add(int curKey, HashNode* myNode) {
    // Calculate the bucket index for the key
    int bucketIndex = calculateHashCode(curKey);
    
    // Set the node's key and hashCode
    myNode->key = curKey;
    myNode->hashCode = bucketIndex;
    
    // If bucket is empty, insert as first node
    if (table[bucketIndex] == nullptr) {
        table[bucketIndex] = myNode;
    } else {
        // Collision occurred - add to the end of the chain
        HashNode* current = table[bucketIndex];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = myNode;
        myNode->prev = current;
    }
    
    numberOfItems++;
    return true;
}

/**
 * @brief Removes a node with the specified key from the hash table.
 * @param curKey The key of the node to remove.
 * @return True if the node was found and removed, false otherwise.
 */
bool HashTable::remove(int curKey) {
    int bucketIndex = calculateHashCode(curKey);
    HashNode* current = table[bucketIndex];
    
    // Search through the chain for the key
    while (current != nullptr) {
        if (current->key == curKey) {
            // Node found - remove it from the chain
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                // This is the first node in the bucket
                table[bucketIndex] = current->next;
            }
            
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            
            delete current;
            numberOfItems--;
            return true;
        }
        current = current->next;
    }
    
    // Key not found
    return false;
}

/**
 * @brief Clears all entries from the hash table.
 */
void HashTable::clear() {
    for (int i = 0; i < numberOfBuckets; i++) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    numberOfItems = 0;
}

/**
 * @brief Retrieves a node with the specified key.
 * @param curKey The key to search for.
 * @return Pointer to the HashNode if found, nullptr otherwise.
 */
HashNode* HashTable::getItem(int curKey) {
    int bucketIndex = calculateHashCode(curKey);
    HashNode* current = table[bucketIndex];
    
    while (current != nullptr) {
        if (current->key == curKey) {
            return current;
        }
        current = current->next;
    }
    
    return nullptr;
}

/**
 * @brief Checks if a node with the specified key exists in the table.
 * @param curKey The key to search for.
 * @return True if the key exists, false otherwise.
 */
bool HashTable::contains(int curKey) {
    return getItem(curKey) != nullptr;
}

/**
 * @brief Prints the entire hash table contents to console and output file.
 */
void HashTable::printTable() {
    std::string message = "\nHere are the Hash Table contents (" + 
                         std::to_string(numberOfItems) + " entries):\n";
    logToFileAndConsole(message);
    
    for (int i = 0; i < numberOfBuckets; i++) {
        std::string bucketMsg = "Bucket " + std::to_string(i) + ": ";
        
        if (table[i] == nullptr) {
            bucketMsg += "Empty";
            logToFileAndConsole(bucketMsg);
        } else {
            // Print all nodes in this bucket's chain
            HashNode* current = table[i];
            bool firstNode = true;
            
            while (current != nullptr) {
                if (firstNode) {
                    firstNode = false;
                } else {
                    bucketMsg += " -> ";
                }
                
                bucketMsg += "Key " + std::to_string(current->key);
                current = current->next;
            }
            
            logToFileAndConsole(bucketMsg);
            
            // Also print detailed node info using printNode()
            current = table[i];
            while (current != nullptr) {
                current->printNode();
                current = current->next;
            }
        }
    }
    logToFileAndConsole("End of table");
}