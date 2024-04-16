/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Ben Foltz-Miranda
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"

#include <iostream>

// TODO: Add your implementation of the buffer class here

/**
 * @brief Construct a new Buffer object
 * @param size the size of the buffer
 */
Buffer::Buffer(int size) {
    buffer = std::vector<buffer_item>(size);
    this->size = size;
    in = 0;
    out = 0;
    count = 0;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&not_full, nullptr);
    pthread_cond_init(&not_empty, nullptr);
}

/**
 * @brief Destroy the Buffer object
 */
Buffer::~Buffer() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
}

/**
 * @brief Insert an item into the buffer
 * @param item the item to insert
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::insert_item(buffer_item item) {
    pthread_mutex_lock(&mutex); // lock the mutex

    while (is_full()) {  // buffer is full
        pthread_cond_wait(&not_full, &mutex); // wait for not full condition
    }

    buffer[in] = item; // insert the item into the buffer
    in = (in + 1) % size; // move the in index
    count++; // increment the count

    pthread_cond_signal(&not_empty); // signal that the buffer is not empty
    pthread_mutex_unlock(&mutex); // unlock the mutex
    return true;
}

/**
 * @brief Remove an item from the buffer
 * @param item the item to remove
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::remove_item(buffer_item* item) {
    pthread_mutex_lock(&mutex); // lock the mutex

    while (is_empty()) { //buffer is empty
        pthread_cond_wait(&not_empty, &mutex); // wait for not empty condition
    }
    *item = buffer[out]; // get the item being removed from the buffer
    out = (out + 1) % size; // move the out index
    count--; // decrement the count

    pthread_cond_signal(&not_full); // signal that the buffer is not empty
    pthread_mutex_unlock(&mutex); // unlock the mutex
    return true;
}

/**
 * @brief Get the size of the buffer
 * @return the size of the buffer
 */
int Buffer::get_size() const { return size; }

/**
 * @brief Get the number of items in the buffer
 * @return the number of items in the buffer
 */
int Buffer::get_count() const { return count; }

/**
 * @brief Chceck if the buffer is empty
 * @return true if the buffer is empty, else false
 */
bool Buffer::is_empty() const { return get_count() == 0; }

/**
 * @brief Check if the buffer is full
 * @return true if the buffer is full, else false
 */
bool Buffer::is_full() const { return get_count() == get_size(); }

/**
 * @brief Print the buffer
 */
void Buffer::print_buffer() const {
    std::cout << "Buffer: [";
    int index = out;
    for (int i = 0; i < count; i++) {
        std::cout << buffer[index];
        if (i < count - 1) {
            std::cout << ", ";
        }
        index = (index + 1) % size;
    }
    std::cout << "]" << std::endl;
}
