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
    float turnAround_time;
    int Time; // for time quantum
};

//======================================= Space for user defined function ============================================//



//======================================== Space for main function =================================================//
int main() {
    
    //asking the user for number of process
    int numberProcess;
    
    printf("Enter the number of process\n");
    scanf("%d",&numberProcess);

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


    //freeing the allocated memory
    free(process);
    process = NULL;
    exit(EXT_SUCCESS);
}
