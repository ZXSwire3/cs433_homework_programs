/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_priority_rr.h"

/**
 * @brief Construct a new SchedulerPriority object
 */
SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) : time_quantum(time_quantum) {
    original_size = 0;
    total_turnaround_time = 0;
    total_waiting_time = 0;
}

/**
 * @brief Destroy the SchedulerPriority object
 */
SchedulerPriorityRR::~SchedulerPriorityRR() = default;

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerPriorityRR::init(vector<PCB>& process_list) {
    // Initialize the scheduler
    for (const auto& i: process_list) {
        priority_pcb_queue.push(i);
    }
    original_size = process_list.size();
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerPriorityRR::print_results() {
    // Print the turnaround time and waiting time for each process
    for (const auto& pair: turnaround_times_map) {
        string process_name = pair.first;
        int turnaround_time = pair.second;
        int waiting_time = waiting_times_map[process_name];
        cout << process_name << " turn-around time = " << turnaround_time << ", waiting time = " << waiting_time
             << endl;
    }

    // Print the results of the simulation
    cout << "Average turn-around time = " << total_turnaround_time / static_cast<double>(original_size)
         << ", Average waiting time = " << total_waiting_time / static_cast<double>(original_size) << endl;
}

/**
 * @brief This function processes a PCB and updates the current time.
 * @param current_process The current process to process
 * @param current_time The current time
 * @param original_burst_times_map The original burst times of the processes
 */
void SchedulerPriorityRR::processPCB(PCB& current_process, int& current_time,
                                     map<string, int>& original_burst_times_map) {
    current_time += current_process.burst_time;
    cout << "Running Process " << current_process.name << " for " << current_process.burst_time << " time units"
         << endl;

    // Calculate the turnaround time
    int turnaround_time = current_time - current_process.arrival_time;
    // Add the turnaround time to the turnaround map
    turnaround_times_map[current_process.name] = turnaround_time;

    // Calculate the waiting time
    int waiting_time = current_time - original_burst_times_map[current_process.name] - current_process.arrival_time;
    // Add the waiting time to the waiting map
    waiting_times_map[current_process.name] = waiting_time;

    // Update the total turnaround time and waiting time
    total_turnaround_time += turnaround_time;
    total_waiting_time += waiting_time;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerPriorityRR::simulate() {
    // Create a map to store the original burst times of the processes
    map<string, int> original_burst_times_map;
    // Create a map to store the pcb queues with the same priority
    map<int, queue<PCB>, greater<int>> priority_map_queues;

    // Loop through the priority queue and add the PCBs to the priority map queues
    while (!priority_pcb_queue.empty()) {
        PCB top_element = priority_pcb_queue.top();
        priority_pcb_queue.pop();

        // Add the original burst time to the map
        original_burst_times_map[top_element.name] = top_element.burst_time;

        // Add the PCB to the priority map queues
        priority_map_queues[top_element.priority].push(top_element);
    }

    int current_time = 0;
    // Loop through the priority map queues
    for (auto& priority_queue_pair: priority_map_queues) {
        // Get the PCB queue with the same priority
        queue<PCB>& pcb_queue = priority_queue_pair.second;

        // Check if there are multiple PCBs with the same priority
        if (pcb_queue.size() > 1) {
            // If there are, run them in a round-robin schedule
            while (!pcb_queue.empty()) {
                PCB current_process = pcb_queue.front();
                pcb_queue.pop();

                // If the burst time is greater than the time quantum and there's more than one PCB left in the queue,
                // run the process for the time quantum
                if (current_process.burst_time > time_quantum && !pcb_queue.empty()) {
                    // Update the remaining burst time and current time
                    current_process.burst_time -= time_quantum;
                    current_time += time_quantum;

                    cout << "Running Process " << current_process.name << " for " << time_quantum << " time units"
                         << endl;

                    // Add the process back to the queue
                    pcb_queue.push(current_process);
                } else {  // Otherwise, run the process normally
                    processPCB(current_process, current_time, original_burst_times_map);
                }
            }
        } else {
            // If there's only one PCB with a certain priority, run it normally
            PCB current_process = pcb_queue.front();
            pcb_queue.pop();

            processPCB(current_process, current_time, original_burst_times_map);
        }
    }
}
