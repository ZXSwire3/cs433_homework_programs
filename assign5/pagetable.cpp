/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Ben Foltz-Miranda
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#include "pagetable.h"

// Constrcutor
PageTable::PageTable(int num_pages) {
    pages.resize(num_pages);
}

// Destructor
PageTable::~PageTable() {
}
