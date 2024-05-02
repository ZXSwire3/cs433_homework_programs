/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.h
 * @author Ben Foltz-Miranda
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#pragma once

#include <unordered_map>

#include "replacement.h"

// A node in the linked list
struct Node {
    int page_num;  // The page number
    Node *prev, *next;  // Pointers to the previous and next nodes
};

/**
 * @brief A class to simulate the least recently used (LRU) page replacement algorithm.
 */
class LRUReplacement : public Replacement {
private:
    std::unordered_map<int, Node *> page_map;  // A map to store the page number and its corresponding node
    Node *head, *tail;  // The head and tail of the linked list
    int next_frame_num = 0;  // The next available frame number

    /**
     * @brief Add a node to the front of the list
     * @param node The node to be added to the list
     */
    void add(Node *node);

    /**
     * @brief Remove a node from the list
     * @param node The node to be removed from the list
     */
    void remove(Node *node);  // Remove a node from the list

public:
    /**
     * @brief Constructor
     * @param num_pages
     * @param num_frames
     */
    LRUReplacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~LRUReplacement();

    /**
     * @brief Accesss a page already in physical memory
     * It may be overridden in a subclass
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num);

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available  frame, not replacement needed
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page, and there is no free frame.
     * Replace the page with the page that has been in memory the longest.
     * @param page_num The logical page number.
     * @return Selected victim page #
     */
    virtual int replace_page(int page_num);

    // Disable copy constructor
    LRUReplacement(const LRUReplacement &) = delete;
    // Disable assignment operator
    LRUReplacement &operator=(const LRUReplacement &) = delete;
};
