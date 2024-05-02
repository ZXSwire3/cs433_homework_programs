/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Ben Foltz-Miranda
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
#include "replacement.h"

#include <iostream>

// Constructor
Replacement::Replacement(int num_pages, int num_frames) : page_table(num_pages) {
    free_frames = num_frames;  // Initialize the number of free frames
    num_references = 0;  // Initialize the number of references
    num_page_faults = 0;  // Initialize the number of page faults
    num_page_replacements = 0;  // Initialize the number of page replacements
}

// Destructor
Replacement::~Replacement() {
    // TOOD: Add your code here
}

// Simulate a single page access
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write) {
    num_references++;  // Increment the count of references

    // If the page is valid, it calls the touch_page function.
    if (page_table[page_num].valid) {
        touch_page(page_num);
        return false;  // no page fault
    }
    // If the page is not valid but free frames are available, it calls the load_page function.
    if (!page_table[page_num].valid && free_frames > 0) {
        load_page(page_num);
        num_page_faults++;  // Increment the count of page faults
        return true;  // page fault
    }
    // If the page is not valid and there is no free frame, it calls the replace_page function.
    if (!page_table[page_num].valid && free_frames == 0) {
        replace_page(page_num);
        num_page_replacements++;  // Increment the count of page replacements
        num_page_faults++;  // Increment the count of page faults
        return true;  // page fault
    }
    return false;  // no page fault
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
    std::cout << "Number of references: \t\t\t" << num_references << std::endl;
    std::cout << "Number of page faults: \t\t\t" << num_page_faults << std::endl;
    std::cout << "Number of page replacements: \t" << num_page_replacements << std::endl;
}
