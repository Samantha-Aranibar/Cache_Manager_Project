/**
 * @file dll_node.cpp
 * @brief Implementation of the DllNode constructor and member function.
 *
 * Contains logic to initialize a node and print its key.
 *
 * @date 12/30/2024 - initial creation and comments
 * @date 05/30/2025 - added additional doxygen style comments
 * @author Hugh Hui
 */

#include <string>

#include "dll_node.h"

extern void logToFileAndConsole(std::string msg);

// Constructor to initialize a node with a specific value
DllNode::DllNode(int value) : key(value), prev(nullptr), next(nullptr) {}

void DllNode::printNode() {
	logToFileAndConsole("Node key: " + std::to_string(key));
}
