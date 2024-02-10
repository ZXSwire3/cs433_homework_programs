/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.cpp
 * @author Ben Foltz-Miranda
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient comments to your code

#include "readyqueue.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructor for the ReadyQueue class.
 */
ReadyQueue::ReadyQueue() {
    count = 0; // Initialize the count to 0
    for (auto & process : queue) {
        process = nullptr; // Initialize each process in the queue to nullptr
    }
}

/**
 *@brief Destructor
 */
ReadyQueue::~ReadyQueue() {
    //  Delete all the PCBs in the table
    for (int i = 0; i < count; i++) {
        queue[i] = nullptr; // Set each process in the queue to nullptr
    }
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    //  When adding a PCB to the queue, you must change its state to READY.
    pcbPtr->setState(ProcState::READY);
    if (count == 0) { // If the queue is empty, add the PCB to the front of the queue
        queue[0] = pcbPtr;
    } else if (pcbPtr->getPriority() > queue[0]->getPriority()) { // If the PCB's priority is greater than the priority of
                                                                  // the PCB at the front of the queue,
        for (int i = count; i > 0; i--) { // Loop through the queue
            queue[i] = queue[i - 1]; // Shift all the PCBs in the queue to the right
        }
        queue[0] = pcbPtr; // Add the PCB to the front of the queue
    } else if (pcbPtr->getPriority() <=
               queue[count - 1]->getPriority()) { // If the PCB's priority is less than the priority of the PCB at
                                                  // the rear of the queue,
        queue[count] = pcbPtr; // Add the PCB to the rear of the queue
    } else { // Otherwise, find the correct position to add the PCB to the queue
        int i = 0; // Holds the index of where the new PCB should be added
        while (pcbPtr->getPriority() <= queue[i]->getPriority()) { // Loop through the queue until the PCB's priority is
                                                                  // greater than the priority of the PCB at the current index
            i++; // Increment the index
        }
        for (int j = count; j > i; j--) { // Loop from the back of the array to the index where the new PCB should be added
            queue[j] = queue[j - 1]; // Shift all the PCBs in the queue to the right
        }
        queue[i] = pcbPtr; // Add the PCB to the queue at the correct position
    }
    count++;
}


/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB *ReadyQueue::removePCB() {
    //  When removing a PCB from the queue, you must change its state to RUNNING.
    if (count == 0) { // If the queue is empty, return nullptr
        return nullptr;
    }
    PCB *removedPCB = queue[0]; // Get the PCB at the front of the queue
    for (int i = 0; i < count - 1; i++) { // Loop through the queue
        queue[i] = queue[i + 1]; // Shift all the PCBs in the queue to the left
    }
    queue[count - 1] = nullptr; // Set the last element in the queue to nullptr
    count--; // Decrement the count
    removedPCB->setState(ProcState::RUNNING); // Set the state of the PCB to RUNNING
    return removedPCB;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return count; // Return the count of PCBs in the queue
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    //  Display the PCBs in the queue.
    cout << "Display Processes in ReadyQueue: " << endl;
    for (int i = 0; i < count; i++) { // Loop through the queue
        cout << "	";
        queue[i]->display();
    }
}
