#ifndef SCHEDULER_H
#define SCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int pid;
        float arrival_time;
        float burst_time;
        int priority;
        float wait_time;
        float turnAround_time;
        float reamining;  
    }Process;

    void fcfs_scheduler(Process process[], int n);
    void sjf_scheduler(Process process[], int n);
    void round_robin_scheduler(Process process[], int n, int quantum);
    void priority_scheduler(Process process[], int n);

#ifdef __cplusplus
}
#endif
#endif

