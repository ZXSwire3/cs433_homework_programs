/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Ben Foltz-Miranda
 * @brief This is the implementation file for the PCBTable class.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient comments to your code

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
    for (int i = 0; i < size; i++) {  // Loop through the size of the PCBTable
        PCB* pcb = new PCB();  // Create a new PCB object on the heap
        processes.push_back(pcb);  // Add the pointer to the vector
    }
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
    // Delete all the PCBs in the table
    for (auto& process: processes) {
        delete process;
        process = nullptr;
    }
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    if (idx < processes.size()) {  // If idx is in range,
        return processes[idx];  // Get the PCB at index "idx" of the PCBTable.
    }
    return nullptr;  // Otherwise, return NULL
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 * @param idx: the index to add the PCB at
 */
void PCBTable::addPCB(PCB* pcb, unsigned int idx) {
    // Check if idx is in range
    if (idx < processes.size()) {
        // Delete the old PCB object at index idx
        delete processes[idx];
        // Add a PCB pointer to the PCBTable at index idx.
        processes[idx] = pcb;
    }
}
