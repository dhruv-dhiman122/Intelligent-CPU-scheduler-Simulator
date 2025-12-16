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
    
    exit(EXT_SUCCESS);
}
