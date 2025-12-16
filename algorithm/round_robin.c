#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//======================================= Space for macro and golbal variables =======================================//

#define EXT_SUCCESS 0
#define EXT_FAILURE 1
#define EXT_FAILURE_NO_VALID_INPUT 1

struct Process {
    int pid;
    float arrival_time;
    float burst_time;
    float wait_time;
    float completion_time;
    float remaining;
    float turnAround_time;
    int Time; // for time quantum
};

//======================================= Space for user defined function ============================================//

void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0, completed = 0;

    for(int i = 0; i < n; i++) {
        proc[i].remaining = proc[i].burst_time;
        proc[i].wait_time = 0;
    }

    while(completed < n) {
        int all_idle = 1;

        for(int i = 0; i < n; i++) {
            if(proc[i].remaining > 0) {
                all_idle = 0;

                int exec_time = (proc[i].remaining < quantum) ? proc[i].remaining : quantum;

                printf("|P %d | %d",proc[i].pid, time+ exec_time);

                for(int j = 0; j < n; j++) {
                    if(j != i && proc[j].remaining > 0) {
                        proc[j].wait_time += exec_time;
                    }
                }

                proc[i].remaining -= exec_time;
                time += exec_time;

                if(proc[i].remaining == 0) {
                    completed++;
                    proc[i].turnAround_time = time;
                }
            }
        }
        if(all_idle) {
            break;
        }
    }
    printf("\n\nProcess\t Brust\tWait time\t Turn around time\n");
    float total_wait = 0, total_turnaround = 0;

    for(int i = 0; i < n; i++) {
        printf("P%d\t%f\t%f\t%f\n",proc[i].pid, proc[i].burst_time, proc[i].wait_time, proc[i].turnAround_time);

        total_wait += proc[i].wait_time;
        total_turnaround += proc[i].turnAround_time;
    }
    printf("\nAvg waiting time: %.2f\n", total_wait / n);
    printf("Avg turn around time is : %.2f\n", total_turnaround / n);
}

//======================================== Space for main function =================================================//
int main() {
    
    //asking the user for number of process
    int numberProcess;
    int time_quantum;
    
    printf("enter the number of process\n");
    scanf("%d",&numberProcess);

    printf("Enter the time for time quantum\n");
    scanf("%d",&time_quantum);

    if(numberProcess <= 0) {
        fprintf(stderr, "PLEASE ENTER A VALID NUMBER!!\n");
        exit(EXT_FAILURE_NO_VALID_INPUT);
    }
    
    //allocating memory to the process
    struct Process* process = (struct Process*)malloc(numberProcess * sizeof(struct Process));

    for(int i = 0; i < numberProcess; i++) {
        process[i].pid = i+1;
        printf("\nEnter the arrival time for the process %d\t",i+1);
        scanf("%f",&process[i].arrival_time);
        
        if(process[i].arrival_time <= 0.0) { // setting the arrival time for respective process as zero
            printf("There was no arrival time set for %d. Thus, making it default value of zero\n",i+1);
            process[i].arrival_time = 0;
        }

        printf("\nEnter the brust time for the process %d\t",i+1);
        scanf("%f",&process[i].burst_time);
        //making them zero
        process[i].wait_time  = 0;
        process[i].completion_time = 0;
        process[i].turnAround_time = 0;
    }
    printf("Done!!\n");
    
    roundRobin(process, numberProcess, time_quantum);

    //freeing the allocated memory
    free(process);
    process = NULL;
    exit(EXT_SUCCESS);
}
