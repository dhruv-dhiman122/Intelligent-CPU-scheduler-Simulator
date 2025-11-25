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

inline void Sort(struct Process process[], int n) {
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

inline void fcfsalgorithm(struct Process process[], int n) {
    
}


//======================================== Space for main function ====================================//

int main() {
    // asking the user for number of input
    int n;
    
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    struct Process* process = (struct Process*)malloc(n * sizeof(struct Process));
    
    for(int i = 0; i < n; i++) { 
        printf("Enter the arrival time for the process %d\n", i+1);
        scanf("%f",&process[i].arrival_time);
        printf("\n");
        printf("Enter the brust time for the process %d\n", i+1);
        scanf("%f",&process[i].brust_time);
    }
    
    free(process);
    exit(EXT_SUCCESS);
}
