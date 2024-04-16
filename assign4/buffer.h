/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Ben Foltz-Miranda
 * @brief header file for the buffer class
 * @version 0.1
 */

#ifndef ASSIGN4_BUFFER_H
#define ASSIGN4_BUFFER_H
#include <pthread.h>

// Define the data type of the buffer items
typedef int buffer_item;
#define BUFFER_SIZE 5

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot exceed the size of the buffer.
 */
class Buffer {
private:
    // TODO: Add your implementation of the buffer class here
    buffer_item *buffer;  // the buffer
    int size;  // the size of the buffer
    int count;  // the number of items in the buffer
    int in;  // the index to insert an item
    int out;  // the index to remove an item
    pthread_mutex_t mutex;
    pthread_cond_t not_full, not_empty;

public:
    /**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */
    Buffer(int size = 5);

    /**
     * @brief Destroy the Buffer object
     */
    ~Buffer();

    /**
     * @brief Insert an item into the buffer
     * @param item the item to insert
     * @return true if successful
     * @return false if not successful
     */
    bool insert_item(buffer_item item);

    /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
    bool remove_item(buffer_item *item);

    /**
     * @brief Get the size of the buffer
     * @return the size of the buffer
     */
    int get_size() const;

    /**
     * @brief Get the number of items in the buffer
     * @return the number of items in the buffer
     */
    int get_count() const;

    /**
     * @brief Chceck if the buffer is empty
     * @return true if the buffer is empty, else false
     */
    bool is_empty() const;
    /**
     * @brief Check if the buffer is full
     * @return true if the buffer is full, else false
     */
    bool is_full() const;

    /**
     * @brief Print the buffer
     */
    void print_buffer() const;
};
#endif  // ASSIGN4_BUFFER_H
