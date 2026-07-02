/**
 * @file dll_node.h
 * @brief Defines the node structure used in a doubly linked list.
 *
 * This header file contains the declaration of the DllNode class,
 * which represents a node in a doubly linked list.
 *
 * @author Hugh Hui
 * @date 12/30/2024 - initial creation
 * @date 05/30/2025 - updated with doxygen style comments
 */

#ifndef NODE_H
#define NODE_H

 /**
  * @class DllNode
  * @brief A node in a doubly linked list.
  *
  * Each DllNode holds an integer key and pointers to its previous and next nodes.
  */
class DllNode {
public:
    int key;         ///< Key value stored in the node.
    DllNode* prev;   ///< Pointer to the previous node.
    DllNode* next;   ///< Pointer to the next node.

    /**
     * @brief Constructs a DllNode with a given key.
     * @param key Integer value to be stored in the node.
     */
    DllNode(int key);

    /**
     * @brief Prints the node's key to console and output file.
     */
    void printNode();
};

#endif // NODE_H
