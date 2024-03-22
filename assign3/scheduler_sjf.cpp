/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_sjf.h"

SchedulerSJF::SchedulerSJF() {
    original_size = 0;
    total_turnaround_time = 0;
    total_waiting_time = 0;
}

SchedulerSJF::~SchedulerSJF() = default;

void SchedulerSJF::init(vector<PCB>& process_list) {
    // Initialize the scheduler
    for (const auto& i: process_list) {
        ready_queue.push(i);
    }
    original_size = ready_queue.size();
}

void SchedulerSJF::print_results() {
    // Print the turnaround time and waiting time for each process
    for (const auto& pair: turnaround_times_map) {
        string process_name = pair.first;
        int turnaround_time = pair.second;
        int waiting_time = waiting_times_map[process_name];
        cout << process_name << " turn-around time = " << turnaround_time << ", waiting time = " << waiting_time
             << endl;
    }

    // Print the results of the simulation
    cout << "Average turn-around time = " << total_turnaround_time / (double) original_size
         << ", Average waiting time = " << total_waiting_time / (double) original_size << endl;
}

void SchedulerSJF::simulate() {
    // Simulate the scheduling of processes in the ready queue
    int current_time = 0;
    // Run the processes in the ready queue
    while (!ready_queue.empty()) {
        PCB current_process = ready_queue.top();
        ready_queue.pop();

        cout << "Running Process " << current_process.name << " for " << current_process.burst_time << " time units"
             << endl;

        // Calculate the turnaround time and waiting time for the current process
        int turnaround_time = current_time + current_process.burst_time - current_process.arrival_time;
        turnaround_times_map[current_process.name] = turnaround_time;

        int waiting_time = current_time - current_process.arrival_time;
        waiting_times_map[current_process.name] = waiting_time;

        // Update the total turnaround time and waiting time
        current_time += current_process.burst_time;
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
    }
}
