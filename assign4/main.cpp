/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Ben Foltz-Miranda
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "buffer.h"

using namespace std;

// global buffer object
Buffer buffer;

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition" << endl;  // shouldn't come here
        }
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);

        if (buffer.remove_item(&item)) {
            cout << "Consumer Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;  // shouldn't come here
        }
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <buffer size> <number of producer threads> <number of consumer threads>"
             << endl;
        exit(1);
    }

    int const sleeptime = stoi(argv[1]);
    int const num_producers = stoi(argv[2]);
    int const num_consumers = stoi(argv[3]);

    cout << "Sleep time: " << sleeptime << " seconds" << endl;
    cout << "Number of producer threads: " << num_producers << endl;
    cout << "Number of consumer threads: " << num_consumers << endl;

    /* TODO: 2. Initialize buffer and synchronization primitives */
    // Initalize pthreads
    pthread_t p_threads[num_producers];
    pthread_t c_threads[num_consumers];

    int thread_ids[num_producers];

    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    for (int i = 0; i < num_producers; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&p_threads[i], nullptr, producer, &thread_ids[i]);
    }

    /* TODO: 4. Create consumer thread(s) */
    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&c_threads[i], nullptr, consumer, nullptr);
    }

    /* TODO: 5. Main thread sleep */
    sleep(sleeptime);
    /* TODO: 6. Exit */
    exit(0);
}
