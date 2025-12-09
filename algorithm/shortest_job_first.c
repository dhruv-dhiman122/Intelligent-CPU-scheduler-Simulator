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

void Sort(struct Process* process, int number) {
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
        printf("\nEnter the brust time for the process %d\t",i+1);
        scanf("%f",&process[i].burst_time);
        //making them zero
        process[i].wait_time  = 0;
        process[i].completion_time = 0;
        process[i].turnAround_time = 0;
    }
    printf("Done!!\n");

    
    //freeing the pointer and not giving chance to be a dangling pointer
    free(process);
    process = NULL;

    exit(EXT_SUCCESS);
}
