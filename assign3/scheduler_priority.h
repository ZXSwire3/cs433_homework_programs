/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.h
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_PRIORITY_H
#define ASSIGN3_SCHEDULER_PRIORITY_H

#include "scheduler.h"
#include <queue>
#include <map>

class SchedulerPriority : public Scheduler {
private:
    // Define a comparison function for the priority queue
    struct ComparePriority {
        bool operator()(const PCB& p1, const PCB& p2) {
            // if two processes have the same priority time, the one with the smaller ID is selected
            if (p1.priority == p2.priority)
                return p1.id > p2.id;
            // otherwise, the one with the higher priority (higher number) is selected
            return p1.priority < p2.priority;
        }
    };
    // The ready queue of processes
    priority_queue<PCB, vector<PCB>, ComparePriority> ready_queue;
    // The original size of the ready queue
    int original_size;
    // The total turnaround time of all processes
    int total_turnaround_time;
    // The total waiting time of all processes
    int total_waiting_time;
    // The turnaround time for each process
    map<string, int> turnaround_times_map;
    // The waiting time for each process
    map<string, int> waiting_times_map;

public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriority();

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriority() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

};


#endif //ASSIGN3_SCHEDULER_PRIORITY_H
