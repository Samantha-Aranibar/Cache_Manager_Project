/**
* @author - Hugh Hui
* @file doubly_linked_list.h -  This header file declares the methods which are coded in the doubly_linked_list.cpp file.
* 12/30/2024 - H. Hui created file and added comments.
*
*/

/**
 * @file doubly_linked_list.h
 * @brief Declaration of the DoublyLinkedList class and its member functions which are coded in the doubly_linked_list.cpp file.
 *
 * This file defines a basic doubly linked list and common operations like
 * insertion, deletion, and movement of nodes.
 *
 * @date 12/30/2024 - initial creation and comments.
 * @date 05/30/2025 - added additional doxygen style comments.
 * @author Hugh Hui
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "dll_node.h"

 /**
  * @class DoublyLinkedList
  * @brief A basic doubly linked list implementation.
  */
class DoublyLinkedList {
public:
    DllNode* head; ///< Pointer to the first node in the list.
    DllNode* tail; ///< Pointer to the last node in the list.

    DoublyLinkedList();  ///< Constructor: Initializes an empty list.
    ~DoublyLinkedList(); ///< Destructor: Deletes all nodes.

    bool isEmpty();                         ///< Checks if the list is empty.
    void insertAtHead(int key);             ///< Inserts a node at the head.
    void insertAtTail(int key);             ///< Inserts a node at the tail.
    void remove(int key);                   ///< Removes a node with a specific key.
    void removeHeaderNode();                ///< Removes the head node.
    void removeTailNode();                  ///< Removes the tail node.
    void moveNodeToHead(int key);           ///< Moves a node to the head.
    void moveNodeToTail(int key);           ///< Moves a node to the tail.
    void clear();                           ///< Deletes all nodes.
    void printList();                       ///< Prints the list from head to tail.
    void reversePrintList();                ///< Prints the list from tail to head.
};

#endif // DOUBLY_LINKED_LIST_H
