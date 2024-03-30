/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_FCFS_H
#define ASSIGN3_SCHEDULER_FCFS_H

#include "scheduler.h"
#include <queue>
/**
 * @brief This Scheduler class implements the FCFS scheduling algorithm.
 */
class SchedulerFCFS : public Scheduler {
private:
    // The ready queue of processes
    queue<PCB> ready_queue;
    // The original size of the ready queue
    int original_size;
    // The total turnaround time of all processes
    int total_turnaround_time;
    // The turnaround time for each process
    vector<int> turnaround_times;
    // The total waiting time of all processes
    int total_waiting_time;
    // The waiting time for each process
    vector<int> waiting_times;

public:
    /**
     * @brief Construct a new SchedulerFCFS object
     */
    SchedulerFCFS();
    /**
     * @brief Destroy the SchedulerFCFS object
     */
    ~SchedulerFCFS() override;

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
#endif //ASSIGN3_SCHEDULER_FCFS_H
