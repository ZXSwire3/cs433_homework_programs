/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_RR_H
#define ASSIGN3_SCHEDULER_RR_H

#include "scheduler.h"
#include <queue>
#include <map>

class SchedulerRR : public Scheduler {
private:
    // The ready queue of processes
    queue<PCB> ready_queue;
    // The original size of the ready queue
    int original_size;
    // The time quantum for the Round Robin algorithm
    int time_quantum;
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
     * @brief Construct a new SchedulerRR object
     */
    SchedulerRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerRR object
     */
    ~SchedulerRR() override;

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


#endif //ASSIGN3_SCHEDULER_RR_H
