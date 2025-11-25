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
};


//======================================== Space for main function ====================================//

int main() {

    exit(EXT_SUCCESS);
}
