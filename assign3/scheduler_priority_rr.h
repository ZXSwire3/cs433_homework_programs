/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.h
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include <map>
#include <queue>

#include "scheduler.h"

class SchedulerPriorityRR : public Scheduler {
private:
    // Define a comparison function for the priority queue
    struct ComparePriority {
        bool operator()(const PCB& p1, const PCB& p2) {
            // if two processes have the same priority, the one with the smaller ID is selected
            if (p1.priority == p2.priority) {
                return p1.id > p2.id;
            }
            // otherwise, the process with the higher priority (higher number) is selected
            return p1.priority < p2.priority;
        }
    };
    priority_queue<PCB, vector<PCB>, ComparePriority> priority_queue;

    int original_size;
    int time_quantum;
    int total_turnaround_time;
    int total_waiting_time;
    map<string, int> turnaround_times_map;
    map<string, int> waiting_times_map;

    void processPCB(PCB& current_process, int& current_time, map<string, int>& original_burst_times_map);

public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriorityRR() override;

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


#endif  // ASSIGN3_SCHEDULER_PRIORITY_RR_H
