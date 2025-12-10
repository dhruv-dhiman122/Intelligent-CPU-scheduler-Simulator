/*
 * Aim of the file -> The files major aim is write code for shortest job first
 * */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//===================================================== Space for Macro or golbal variable ========================================//

#define EXT_SUCCESS 0
#define EXT_FAILURE 1
#define EXT_FAILURE_NO_PROCESS 1
struct Process {
    long pid;
    float arrival_time;
    float burst_time;
    float wait_time;
    float completion_time;
    float turnAround_time;
};

//==================================================== Space for user defined function ============================================//

void Sort(struct Process* process, int number) { // sorting according to the burst time
    for(int i = 0; i < number; i++) {
        for(int j = 0; j < number-i-1; j++) {
            if(process[j].burst_time > process[j+1].burst_time) {
                struct Process temp = process[j];
                process[j] = process[j+1];
                process[j+1] = temp;
            }
        }
    }
}

void scheduling(struct Process* process, int n) { 
    int completed = 0;
    float current_time = 0;
    int isCompleted[n];

    for(int i = 0; i < n; i++) {
        isCompleted[i] = 0;
    }

    while(completed < n) {
        int idx = -1;
        float minBurst = 1e9;

        for(int i = 0; i < n; i++) {
            if(process[i].arrival_time <= current_time && !isCompleted[i]) {
                if(process[i].burst_time < minBurst) {
                    minBurst = process[i].burst_time;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            float startTime = (current_time > process[idx].arrival_time) ? current_time : process[idx].arrival_time;
            
            process[idx].completion_time = startTime + process[idx].burst_time;
            process[idx].turnAround_time = process[idx].completion_time - process[idx].arrival_time;
            process[idx].wait_time = process[idx].turnAround_time - process[idx].burst_time;
            current_time = process[idx].completion_time;

            isCompleted[idx] = 1;
            completed++;

            printf("process = %ld, Arrival Time = %.2f, Brust time = %.2f, start = %.2f, completion time = %.2f, turn around time = %.2f, waiting time = %.2f\n", process[idx].pid, process[idx].arrival_time, process[idx].burst_time, startTime, process[idx].completion_time,
                    process[idx].turnAround_time, process[idx].wait_time);
        }
        else {
            current_time++;
        }
    }
}

//================================================== Space for main function ========================================================//
int main() {
    //================== Space for variable defined within main function ====================================//
    int numberProcess;
    //asking the user for number of process
    
    printf("Enter the number of process\n");
    scanf("%d",&numberProcess);
   
    if(numberProcess <= 0) {
        fprintf(stderr,"ERR ENTER ATLEAST ONE PROCESS!!");
        exit(EXT_FAILURE_NO_PROCESS);
    }

    struct Process* process = (struct Process *)malloc(numberProcess * sizeof(struct Process)); // allocating the memory
    
    //taking input from the user
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

    //calling function
    
    //freeing the pointer and not giving chance to be a dangling pointer
    free(process);
    process = NULL;

    exit(EXT_SUCCESS);
}
