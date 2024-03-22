/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_SJF_H
#define ASSIGN3_SCHEDULER_SJF_H

#include "scheduler.h"
#include <queue>
#include <map>

class SchedulerSJF : public Scheduler {
private:
    // Define a comparison function for the priority queue
    struct CompareBurstTime {
        bool operator()(const PCB& p1, const PCB& p2) {
            // return "true" if "p1" is ordered before "p2", for example:
            return p1.burst_time > p2.burst_time;
        }
    };
    priority_queue<PCB, vector<PCB>, CompareBurstTime> ready_queue;
    int original_size;
    int total_turnaround_time;
    int total_waiting_time;
    map<string, int> turnaround_times_map;
    map<string, int> waiting_times_map;

public:
    /**
     * @brief Construct a new SchedulerSJF object
     */
    SchedulerSJF();
    /**
     * @brief Destroy the SchedulerSJF object
     */
    ~SchedulerSJF() override;
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
#endif //ASSIGN3_SCHEDULER_SJF_H
