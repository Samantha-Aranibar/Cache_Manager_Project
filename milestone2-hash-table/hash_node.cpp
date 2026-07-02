/**
 * @file hash_node.cpp
 * @brief Implementation file for the HashNode class.
 *
 * This file contains the definitions for the constructor and methods of the HashNode class.
 *
 * @date 09/23/24 - Created by ChatGPT
 * @date 10/17/24 - Modified by jhui
 * @date 01/11/25 - Modified by hhui; 1) added calculateHashCode, 2) modified methods to include hash table size parameter
 * @date 05/31/25 - Added additional Doxygen-style comments
 */

#include "hash_node.h"
#include <iostream>

 /**
  * @brief Constructs a HashNode with the provided key and contact information.
  *
  * @param val The integer key associated with this node.
  * @param myFullName Full name of the person or entity.
  * @param myAddress Street address.
  * @param myCity City.
  * @param myState State.
  * @param myZip ZIP code.
  *
  * The node initializes all data members and sets both `prev` and `next` pointers to nullptr.
  */
HashNode::HashNode(int val, std::string myFullName, std::string myAddress, std::string myCity, std::string myState, std::string myZip)
	: key(val), fullName(myFullName), address(myAddress), city(myCity), state(myState), zip(myZip), prev(nullptr), next(nullptr) {}

/**
 * @brief Prints the contents of the HashNode.
 *
 * This method logs the node's key to the console and output file. If the `verbose` flag is set to true,
 * it logs the full details (name, address, city, state, zip). This function is primarily used for debugging
 * and inspecting the contents of the node.
 */
void HashNode::printNode() {
	bool verbose = false;
	if (verbose) {
		logToFileAndConsole("FIFO info from cacheManager.  Node key: " + std::to_string(key) + "; name: " + fullName + ";address: " + address + "; city: " + city + "; state: " + state + "; zip: " + zip);
	}
	else {
		logToFileAndConsole("FIFO info from cacheManager:  Node key: " + std::to_string(key));
	}
}
