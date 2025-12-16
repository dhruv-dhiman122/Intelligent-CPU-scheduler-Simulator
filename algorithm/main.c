#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "scheduler.h"

//============================================= Space for gobal variable and macro =====================================//

#define EXT_SUCCESS 0
#define EXT_FAILURE 1

//================================================== Space for extern function ==========================================//

extern void fcfs_scheduler(Process process[], int n);
extern void sjf_scheduler(Process process[], int n);
extern void round_robin_scheduler(Process process[], int n, int quantum);
extern void priority_scheduler(Process process[], int n);

//=============================================== Space for user defined function ====================================//

void print_result(Process process[], int n, const char* algorithm_name) {
    printf("\n=============================================");
    printf("%s scheduling result\n", algorithm_name);
    printf("===============================================\n");
    printf("PID | Arrival | Burst | Priority | Waiting | turn around time\n");

    float total_waiting = 0, total_turnaround = 0;

    for(int i = 0; i < n; i++) {
        printf("%3d | %7f | %5f | %8d | %7f | %10f\n", process[i].pid, process[i].arrival_time, process[i].burst_time, process[i].priority, process[i].wait_time, process[i].turnAround_time);

        total_waiting = process[i].wait_time;
        total_turnaround = process[i].turnAround_time;
    }
    printf("\nStatistics:\n");
    printf("Avg Waiting time: %.2f\n", total_waiting / n);
    printf("Avg turn around time %.2f\n", total_turnaround / n);
}

void copy_process_array(Process dest[], Process src[], int n) {
    for(int i = 0; i < n; i++)  {
        dest[i] = src[i];
    }
}

//============================================= Space for main function ========================================//
int main() {
    // ======== ADD THIS SECTION ========
    // Define test data FIRST
    Process test_processes[] = {
        {1, 0.0, 10.0, 3, 0.0, 0.0, 0.0},
        {2, 1.0, 5.0, 1, 0.0, 0.0, 0.0},
        {3, 2.0, 8.0, 4, 0.0, 0.0, 0.0}
    };
    
    int n = sizeof(test_processes) / sizeof(test_processes[0]);
    // ==================================
    
    printf("🚀 CPU Scheduler Simulator\n");
    printf("============================\n");
    printf("Testing with %d processes\n\n", n);
    
    // Create copies for each scheduler
    Process fcfs_copy[n], sjf_copy[n], rr_copy[n], priority_copy[n];
    
    copy_process_array(fcfs_copy, test_processes, n);
    copy_process_array(sjf_copy, test_processes, n);
    copy_process_array(rr_copy, test_processes, n);
    copy_process_array(priority_copy, test_processes, n);
    
    // Run all schedulers
    printf("1️⃣  Running FCFS...\n");
    fcfs_scheduler(fcfs_copy, n);
    print_result(fcfs_copy, n, "FCFS");
    
    printf("\n2️⃣  Running SJF...\n");
    sjf_scheduler(sjf_copy, n);
    print_result(sjf_copy, n, "SJF");
    
    printf("\n3️⃣  Running Round Robin (Quantum = 2)...\n");
    round_robin_scheduler(rr_copy, n, 2);
    print_result(rr_copy, n, "Round Robin");
    
    printf("\n4️⃣  Running Priority...\n");
    priority_scheduler(priority_copy, n);
    print_result(priority_copy, n, "Priority");
    
    printf("\n✅ All schedulers completed successfully!\n");
    exit(EXT_SUCCESS);
}
