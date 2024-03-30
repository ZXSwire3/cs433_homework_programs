/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Ben Foltz-Miranda
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_priority_rr.h"

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) : time_quantum(time_quantum) {
    original_size = 0;
    total_turnaround_time = 0;
    total_waiting_time = 0;
}

SchedulerPriorityRR::~SchedulerPriorityRR() = default;

void SchedulerPriorityRR::init(vector<PCB>& process_list) {
    // Initialize the scheduler
    for (const auto& i: process_list) {
        priority_queue.push(i);
    }
    original_size = process_list.size();
}

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
    cout << "Average turn-around time = " << total_turnaround_time / (double) original_size
         << ", Average waiting time = " << total_waiting_time / (double) original_size << endl;
}

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

void SchedulerPriorityRR::simulate() {
    map<string, int> original_burst_times_map;
    map<int, queue<PCB>, greater<int>> priorityQueues;

    while (!priority_queue.empty()) {
        PCB topElement = priority_queue.top();
        priority_queue.pop();

        original_burst_times_map[topElement.name] = topElement.burst_time;

        priorityQueues[topElement.priority].push(topElement);
    }

    int current_time = 0;
    for (auto& priority_queue_pair: priorityQueues) {
        queue<PCB>& pcb_queue = priority_queue_pair.second;

        // Check if there are multiple PCBs with the same priority
        if (pcb_queue.size() > 1) {
            // If there are, run them in a round-robin schedule
            while (!pcb_queue.empty()) {
                PCB current_process = pcb_queue.front();
                pcb_queue.pop();

                // If the burst time is greater than the time quantum and there's more than one PCB left in the queue,
                // run the process for the time quantum
                if (current_process.burst_time > time_quantum && pcb_queue.size() > 0) {
                    // Update the remaining burst time and current time
                    current_process.burst_time -= time_quantum;
                    current_time += time_quantum;

                    cout << "Running Process " << current_process.name << " for " << time_quantum << " time units"
                         << endl;

                    // Add the process back to the queue
                    pcb_queue.push(current_process);
                } else {
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
