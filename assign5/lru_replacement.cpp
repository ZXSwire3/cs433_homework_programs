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
    delete head; // Delete the head node
    delete tail; // Delete the tail node
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
    // Get the page number of the victim page
    Node* victim = tail->prev;
    // Remove the victim page from the map
    page_map.erase(victim->page_num);
    // Remove the victim page from the list
    remove(victim);

    // Create a new page entry
    PageEntry new_page;
    // Set the page as valid
    new_page.valid = true;
    // Set the frame number
    new_page.frame_num = victim->page_num;
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
    page_table[victim->page_num].valid = false;

    // Return the page number of the page to be replaced
    return victim->page_num;
}

void LRUReplacement::add(Node* node) {
    // Create a temporary node to store the next node
    Node* temp = head->next;
    // Set the new node's next and prev pointers
    node->next = temp;
    node->prev = head;
    // Set the head's next and the next node's prev pointers
    head->next = node;
    temp->prev = node;
}

void LRUReplacement::remove(Node* node) {
    // Create pointers to the previous and next nodes
    Node* prev_node = node->prev;
    Node* next_node = node->next;
    // Set the previous and next nodes' pointers
    prev_node->next = next_node;
    next_node->prev = prev_node;
}
