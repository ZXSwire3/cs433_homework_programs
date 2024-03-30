/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_rr.h"

/**
 * @brief Construct a new SchedulerRR object
 */
SchedulerRR::SchedulerRR(int time_quantum) : time_quantum(time_quantum) {
    original_size = 0;
    total_turnaround_time = 0;
    total_waiting_time = 0;
}

/**
 * @brief Destroy the SchedulerRR object
 */
SchedulerRR::~SchedulerRR() = default;

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerRR::init(vector<PCB>& process_list) {
    // Initialize the scheduler
    for (const auto& i: process_list) {
        ready_queue.push(i);
    }
    original_size = ready_queue.size();
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerRR::print_results() {
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

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerRR::simulate() {
    // Simulate the scheduling of processes in the ready queue
    int current_time = 0;
    map<string, int> original_burst_times_map;

    // Run the processes in the ready queue
    while (!ready_queue.empty()) {
        PCB current_process = ready_queue.front();
        ready_queue.pop();

        // If the process is running for the first time, add the burst time to the original burst times map
        if (original_burst_times_map.find(current_process.name) == original_burst_times_map.end()) {
            original_burst_times_map[current_process.name] = current_process.burst_time;
        }

        // If the burst time is greater than the time quantum, run the process for the time quantum
        if (current_process.burst_time > time_quantum) {
            // Update the remaining burst time and current time
            current_process.burst_time -= time_quantum;
            current_time += time_quantum;

            cout << "Running Process " << current_process.name << " for " << time_quantum << " time units" << endl;

            // Add the process back to the ready queue
            ready_queue.push(current_process);
        } else {  // If the burst time is less than or equal to the time quantum, run the process for the remaining
                  // burst time
            current_time += current_process.burst_time;

            cout << "Running Process " << current_process.name << " for " << current_process.burst_time << " time units"
                 << endl;

            // Calculate the turnaround time
            int turnaround_time = current_time - current_process.arrival_time;
            // Add the turnaround time to the turnaround map
            turnaround_times_map[current_process.name] = turnaround_time;

            // Calculate the waiting time
            int waiting_time =
                    current_time - original_burst_times_map[current_process.name] - current_process.arrival_time;
            // Add the waiting time to the waiting map
            waiting_times_map[current_process.name] = waiting_time;

            // Update the total turnaround time and waiting time
            total_turnaround_time += turnaround_time;
            total_waiting_time += waiting_time;
        }
    }
}
