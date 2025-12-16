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


//============================================= Space for main function ========================================//
int main() {
    
    exit(EXT_SUCCESS);
}
