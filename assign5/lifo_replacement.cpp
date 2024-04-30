/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Ben Foltz-Miranda
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

// TODO: Add your implementation here
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {
    // TODO: Add additional implementation code
    free_frames = num_frames;
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
LIFOReplacement::~LIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    // The page is not in the page table, so we need to load it
    PageEntry new_page;
    new_page.valid = true;
    new_page.frame_num = next_frame_num;

    // Add the page number to the FIFO queue
    page_stack.push(page_num);

    // Decrememnt the count of free frames
    free_frames--;

    // Update the page table
    page_table[page_num] = new_page;

    // Increment the next available frame number
    next_frame_num++;
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    // The page is not in the page table, so we need to load it
    PageEntry new_page;
    new_page.valid = true;

    // Get the page number of the page to be replaced
    int victim_page = page_stack.top();
    page_stack.pop();

    // Add the page number to the FIFO queue
    page_stack.push(page_num);

    // Update the page table
    page_table[page_num] = new_page;
    page_table[victim_page].valid = false;

    return victim_page;
    // return 0;
}
