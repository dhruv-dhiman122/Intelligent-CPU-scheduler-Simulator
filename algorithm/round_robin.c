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



    //freeing the allocated memory
    free(process);
    process = NULL;
    exit(EXT_SUCCESS);
}
