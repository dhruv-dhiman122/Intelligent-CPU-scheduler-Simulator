/*
 * FCFS -> this is the algorithm that focuses over the arrival time of the processes and allocates accordingly 
 * */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

//======================================== Space for macro or global variables =================================//

#define EXT_SUCCESS 0
#define EXT_FAILURE 1

//======================================= Sapce for user-defined function ============================//

struct Process {
    long long pid;
    float arrival_time;
    float brust_time;
    float waiting_time;
    float turnaround_time;
    float response_time;
    float completion_time;
};

void Sort(struct Process process[], int n) {
    struct Process temp;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(process[j].arrival_time > process[j+1].arrival_time) {
                temp = process[j+1];
                process[j+1] = process[j];
                process[j] = temp;
            }
        }
    }
}

void fcfsalgorithm(struct Process process[], int n) {
    int current_time = 0;

    for(int i = 0; i < n; i++) {
        if(current_time < process[i].arrival_time) {
            current_time = process[i].arrival_time;
        }

        process[i].completion_time  = current_time + process[i].brust_time;
        process[i].turnaround_time  = process[i].completion_time - process[i].arrival_time;
        process[i].waiting_time = process[i].turnaround_time - process[i].brust_time;

        current_time = process[i].completion_time;
    }
}

void displayResults(struct Process processes[], int n) {
    float avg_waiting = 0, avg_turnaround = 0;
    
    printf("\n=== FCFS Scheduling Results ===\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    
    for (int i = 0; i < n; i++) {
        printf("%lld\t%f\t%f\t%f\t\t%f\t\t%f\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].brust_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
        
        avg_waiting += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround / n);
}
//======================================== Space for main function ====================================//

int main() {
    // asking the user for number of input
    int n;
    
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    struct Process* process = (struct Process*)malloc(n * sizeof(struct Process));
    
    for(int i = 0; i < n; i++) { 
        //asking the user about arrival time
        printf("Enter the arrival time for the process %d\n", i+1);
        scanf("%f",&process[i].arrival_time);
        if(process[i].arrival_time <= 0) {
            process[i].arrival_time = 0;
        }
        //asking the user about brust time
        printf("\n");
        printf("Enter the brust time for the process %d\n", i+1);
        scanf("%f",&process[i].brust_time);
    }
    
    //calling the function made
    Sort(process, n);

    fcfsalgorithm(process,n);

    displayResults(process, n);
    free(process);
    exit(EXT_SUCCESS);
}
