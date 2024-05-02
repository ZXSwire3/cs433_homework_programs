/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Ben Foltz-Miranda
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#include "lru_replacement.h"

LRUReplacement::LRUReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {
    free_frames = num_frames;  // Initialize the number of free frames
    head = new Node();  // Initialize the head of the list
    tail = new Node();  // Initialize the tail of the list
    head->next = tail;  // Set the head's next pointer to the tail
    tail->prev = head;  // Set the tail's prev pointer to the head
}

LRUReplacement::~LRUReplacement() {
    Node* current = head;  // Set the current node to the head
    while (current != nullptr) {
        Node* next_node = current->next;  // Set the next node
        delete current;  // Delete the current node
        current = next_node;  // Set the current node to the next node
    }
}

// Accesss a page already in physical memory
void LRUReplacement::touch_page(int page_num) {
    // Get the node from the page map
    Node* node = page_map[page_num];
    // Remove the node from the list
    remove(node);
    // Add the node to the front of the list
    add(node);
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    // Create a new page entry
    PageEntry new_page;
    // Set the page as valid
    new_page.valid = true;
    // Set the frame number
    new_page.frame_num = next_frame_num;
    // Set the dirty bit
    new_page.dirty = false;
    // Update the page table
    page_table[page_num] = new_page;

    // Create a new node
    Node* node = new Node();
    // Set the node's page number
    node->page_num = page_num;
    // Add the node to the map
    page_map[node->page_num] = node;
    // Add the node to the front of the list
    add(node);

    // Decrement the count of free frames
    free_frames--;

    // Increment the next available frame number
    next_frame_num++;
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    // Get the victim page node from the linked list
    Node* victim = tail->prev;
    // Remove the victim page number from the map
    page_map.erase(victim->page_num);
    // Remove the victim page from the linked list
    remove(victim);
    // Get the page number of the page to be replaced
    int victim_page_number = victim->page_num;
    // Delete the victim node
    delete victim;


    // Create a new page entry
    PageEntry new_page;
    // Set the page as valid
    new_page.valid = true;
    // Set the frame number
    new_page.frame_num = victim_page_number;
    // Set the dirty bit
    new_page.dirty = true;

    // Create a new node
    Node* node = new Node();
    // Set the node's page number
    node->page_num = page_num;
    // Add the node to the map
    page_map[page_num] = node;
    // Add the new node to the front of the list
    add(node);

    // Update the page table
    page_table[page_num] = new_page;
    // Set the replaced page as invalid
    page_table[victim_page_number].valid = false;

    // Return the page number of the page to be replaced
    return victim_page_number;
}

void LRUReplacement::add(Node* new_node) {
    // Create a node to store the node after the head
    Node* temp = head->next;
    // Set the new node's next node point to the temp node
    new_node->next = temp;
    // Set the new node's prev node point to the head
    new_node->prev = head;
    // Set the head's next node point to the new node
    head->next = new_node;
    // Set the temp node's prev node point to the new node
    temp->prev = new_node;
}

void LRUReplacement::remove(Node* node) {
    // Create a node to store the node previous to the node to be removed
    Node* prev_node = node->prev;
    // Create a node to store the node next to the node to be removed
    Node* next_node = node->next;
    // Set the previous node's next node point to the next node
    prev_node->next = next_node;
    // Set the next node's previous node point to the previous node
    next_node->prev = prev_node;
}
