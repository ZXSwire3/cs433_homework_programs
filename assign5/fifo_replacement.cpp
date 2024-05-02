/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Ben Foltz-Miranda
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {
    free_frames = num_frames;  // Initialize the number of free frames
}

FIFOReplacement::~FIFOReplacement() {}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // Create a new page entry
    PageEntry new_page;
    // Set the page as valid
    new_page.valid = true;
    // Set the frame number
    new_page.frame_num = next_frame_num;
    // Set the dirty bit
    new_page.dirty = false;

    // Add the page number to the FIFO queue
    page_queue.push(page_num);

    // Decrememnt the count of free frames
    free_frames--;

    // Update the page table
    page_table[page_num] = new_page;

    // Increment the next available frame number
    next_frame_num++;
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // Create a new page entry
    PageEntry new_page;
    // Set the page as valid
    new_page.valid = true;
    // Set the frame number
    new_page.frame_num = next_frame_num;
    // Set the dirty bit
    new_page.dirty = true;

    // Get the page number of the page to be replaced
    int victim_page = page_queue.front();
    // Remove the page number from the FIFO queue
    page_queue.pop();

    // Add the page number to the FIFO queue
    page_queue.push(page_num);

    // Update the page table
    page_table[page_num] = new_page;
    // Set the replaced page as invalid
    page_table[victim_page].valid = false;

    // Return the page number of the page to be replaced
    return victim_page;
}
