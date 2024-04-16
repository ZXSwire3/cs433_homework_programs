/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Ben Foltz-Miranda
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

#include "buffer.h"

#include <iostream>

/**
 * @brief Construct a new Buffer object
 * @param size the size of the buffer
 */
Buffer::Buffer(int size) {
    buffer = std::queue<buffer_item>();  // initialize the buffer
    this->size = size;  // set the size of the buffer
    count = 0;  // initialize the count to 0
    pthread_mutex_init(&mutex, nullptr);  // initialize the mutex
    pthread_cond_init(&not_full, nullptr);  // initialize the not full condition
    pthread_cond_init(&not_empty, nullptr);  // initialize the not empty condition
}

/**
 * @brief Destroy the Buffer object
 */
Buffer::~Buffer() {
    pthread_mutex_destroy(&mutex);  // destroy the mutex
    pthread_cond_destroy(&not_full);  // destroy the not full condition
    pthread_cond_destroy(&not_empty);  // destroy the not empty condition
}

/**
 * @brief Insert an item into the buffer
 * @param item the item to insert
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::insert_item(buffer_item item) {
    pthread_mutex_lock(&mutex);  // lock the mutex

    while (is_full()) {  // buffer is full
        pthread_cond_wait(&not_full, &mutex);  // wait for not full condition
    }

    buffer.push(item);  // insert the item into the buffer
    count++;  // increment the count

    pthread_cond_signal(&not_empty);  // signal that the buffer is not empty
    pthread_mutex_unlock(&mutex);  // unlock the mutex
    return true;
}

/**
 * @brief Remove an item from the buffer
 * @param item the item to remove
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::remove_item(buffer_item* item) {
    pthread_mutex_lock(&mutex);  // lock the mutex

    while (is_empty()) {  // buffer is empty
        pthread_cond_wait(&not_empty, &mutex);  // wait for not empty condition
    }

    *item = buffer.front();  // get the item being removed from the buffer
    buffer.pop();  // remove the first item from the buffer
    count--;  // decrement the count

    pthread_cond_signal(&not_full);  // signal that the buffer is not empty
    pthread_mutex_unlock(&mutex);  // unlock the mutex
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

    std::queue<buffer_item> buffer_copy = buffer;  // copy the buffer
    while (!buffer_copy.empty()) {
        std::cout << buffer_copy.front();  // print the front of the buffer
        buffer_copy.pop();  // remove the front of the buffer
        if (!buffer_copy.empty()) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
}
