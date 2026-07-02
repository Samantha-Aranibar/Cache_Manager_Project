/**
 * @file doubly_linked_list.cpp
 * @brief Implementation of the DoublyLinkedList class.
 *
 * This file defines the member functions declared in doubly_linked_list.h.
 * It provides core doubly-linked list operations used by the CacheManager’s
 * FIFO policy: insertion/removal at head or tail, node movement, traversal,
 * clearing, and bidirectional printing for verification.
 *
 * Helper utilities (findNode and detach) support modular list manipulation.
 *
 * @date 10/06/2025 - Initial creation with constructor, destructor, and
 *                    basic insert/remove methods.
 * @date 10/07/2025 - Added helper functions (findNode, detach), move
 *                    operations (moveNodeToHead, moveNodeToTail), and clear().
 * @date 10/09/2025 - Added printList(), reversePrintList(), and integrated
 *                    logging output.
 * @date 10/10/2025 - Implemented getSize() and updated documentation for
 *                    milestone 3 submission.
 * 
 * @author 
 *  Samantha Aranibar Valdes
 *  Ayush Rangrej
 */

#include "doubly_linked_list.h"
#include "dll_node.h"
#include <string>

extern void logToFileAndConsole(std::string msg);

/**
 * @brief Constructs an empty list with null head/tail and size 0.
 */
DoublyLinkedList::DoublyLinkedList() { 
    head = nullptr;
    tail = nullptr;
    size = 0; 
} 

/**
 * @brief Destroys the list by clearing all nodes.
 */
DoublyLinkedList::~DoublyLinkedList() { clear(); }                   
    
/**
 * @brief Finds a node by key.
 * @return Pointer to the matching node, or nullptr if not found.
 */
static DllNode* findNode(DllNode* head, int key) {
    for (DllNode* cur = head; cur; cur = cur->next) {
        if (cur->key == key) return cur;
    }
    return nullptr; 
}

/**
 * @brief Detaches a node from the list without deleting it.
 */
static void detach(DllNode*& head, DllNode*& tail, DllNode* n) {
    if (!n) return;
    if (n->prev) n->prev->next = n->next; else head = n->next;
    if (n->next) n->next->prev = n->prev; else tail = n->prev;
    n->prev = n->next = nullptr;
}



/**
 * @brief Checks if the list is empty.
 * @return true if the list has no nodes, false otherwise.
 */
bool DoublyLinkedList::isEmpty() { return head == nullptr; }

/**
 * @brief Gets the number of nodes in the list.
 * @return The total count of nodes.
 */
int DoublyLinkedList::getSize() {
    int count = 0;
    for (DllNode* cur = head; cur; cur = cur->next) {
        count++;
    }
    return count;
}


/**
 * @brief Inserts a new node at the beginning of the list.
 * @param key The key value for the new node.
 */
void DoublyLinkedList::insertAtHead(int key, DllNode* newNode) {
    if (!newNode) return;
    newNode->next = head;
    if (head) head->prev = newNode; else tail = newNode;
    head = newNode;
}


/**
 * @brief Inserts a new node at the end of the list.
 * @param key The key value for the new node.
 */
void DoublyLinkedList::insertAtTail(int key, DllNode* newNode) {
    if (!newNode) return;
    newNode->prev = tail;
    if (tail) tail->next = newNode; else head = newNode;
    tail = newNode;
}


/**
 * @brief Removes the first node with a matching key.
 * @param key The key value of the node to remove.
 */
void DoublyLinkedList::remove(int key) {
    DllNode* n = findNode(head, key); 
    if (!n) return;       
    detach(head, tail, n); 
    delete n;             
}


/**
 * @brief Removes the head node of the list.
 */
void DoublyLinkedList::removeHeaderNode() {
    if (!head) return;    
    DllNode* n = head;     
    detach(head, tail, n);
    delete n;              
}


/**
 * @brief Removes the tail node of the list.
 */
void DoublyLinkedList::removeTailNode() {
    if (!tail) return;      
    DllNode* n = tail;      
    detach(head, tail, n);  
    delete n;               
}


/**
 * @brief Moves the node with the given key to the head.
 * @param key The key value of the node to move.
 */
void DoublyLinkedList::moveNodeToHead(int key) {
    DllNode* n = findNode(head, key);
    if (!n || n == head) return;     
    detach(head, tail, n);           
    n->next = head;                   
    if (head) head->prev = n; else tail = n;
    head = n;
}


/**
 * @brief Moves the node with the given key to the tail.
 * @param key The key value of the node to move.
 */
void DoublyLinkedList::moveNodeToTail(int key) {
    DllNode* n = findNode(head, key);         
    if (!n || n == tail) return;              
    detach(head, tail, n);                   
    n->prev = tail;                         
    if (tail) tail->next = n; else head = n; 
    tail = n;                                 
}


/**
 * @brief Deletes all nodes from the list and resets head/tail.
 */
void DoublyLinkedList::clear() {
    DllNode* cur = head;            
    while (cur) {                   
        DllNode* nxt = cur->next;   
        delete cur;                 
        cur = nxt;                 
    }                                          
    head = tail = nullptr;        
}


/**
 * @brief Prints the list from head to tail.
 * Logs output to both console and file using logToFileAndConsole.
 */
void DoublyLinkedList::printList() {
    logToFileAndConsole("Here are the List contents:");
    for (DllNode* cur = head; cur; cur = cur->next) cur->printNode();
    logToFileAndConsole("End of List");
}

/**
 * @brief Prints the list from tail to head.
 * Logs output to both console and file using logToFileAndConsole.
 */
void DoublyLinkedList::reversePrintList() {
    logToFileAndConsole("Here are the List contents reversed:");
    for (DllNode* cur = tail; cur; cur = cur->prev) cur->printNode(); 
    logToFileAndConsole("End of List");
}
