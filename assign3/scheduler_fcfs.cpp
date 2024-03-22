/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and
// member functions init, print_results, and simulate here
SchedulerFCFS::SchedulerFCFS() { ready_queue = queue<PCB>(); }

SchedulerFCFS::~SchedulerFCFS() {
    // Destructor
}

void SchedulerFCFS::init(vector<PCB>& process_list) {
    // Initialize the scheduler
    for (const auto& i: process_list) {
        ready_queue.push(i);
    }
    original_size = ready_queue.size();
}

void SchedulerFCFS::print_results() {
    for (int i = 0; i < waiting_times.size(); ++i) {
        cout << "T" << i << " turn-around time = " << turnaround_times[i] << ", waiting time = " << waiting_times[i]
             << endl;
    }

    // Print the results of the simulation
    cout << "FCFS Scheduler Results" << endl;
    cout << "Average turn-around time = " << total_turnaround_time / (double) original_size
         << ", Average waiting time = " << total_waiting_time / (double) original_size
         << endl;
}

void SchedulerFCFS::simulate() {
    // Simulate the scheduling of processes in the ready queue
    int current_time = 0;
    // Run the processes in the ready queue
    while (!ready_queue.empty()) {
        PCB current_process = ready_queue.front();
        ready_queue.pop();

        cout << "Running Process " << current_process.name << " for " << current_process.burst_time << " time units"
             << endl;

        // Calculate the turnaround time and waiting time for the current process
        int turnaround_time = current_time + current_process.burst_time - current_process.arrival_time;
        turnaround_times.push_back(turnaround_time);

        int waiting_time = current_time - current_process.arrival_time;
        waiting_times.push_back(waiting_time);

        // Update the total turnaround time and waiting time
        current_time += current_process.burst_time;
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
    }
}
