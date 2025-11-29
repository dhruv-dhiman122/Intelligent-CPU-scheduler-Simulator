/*
 * Priority Scheduling:- This is basically where the computer schedule the process according to their priority order
 *                       If the priority order is same then it jumps back to FCFS algorithm
 * */


#include <iostream>
#include <queue>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iomanip>
//============================== user made space for struct and classes ==========================//

struct Process {
    int pid;
    int priority;
    float arrival_time;
    float burst_time;
    float completion_time;
    float turnaround_time;
    float wait_time;
};

//============================= Space for macro or global variables =====================//

#define EXT_SUCCESS 0
#define EXT_FAILURE 1

//================================ Space for user defined functions ========================//

void printProcessTable(const std::vector<Process>& process) {
    std::cout<<"\nProcess Table:\n";
    std::cout << std::setw(5) << "PID" << std::setw(10) << "Priority" 
              << std::setw(12) << "Arrival" << std::setw(10) << "Burst"
              << std::setw(12) << "Complete" << std::setw(12) << "Turnaround"
              << std::setw(10) << "Wait" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    float total_tat = 0, total_wt = 0;

    for(const auto& p : process) {
        std::cout << std::setw(5) << p.pid 
                  << std::setw(10) << p.priority
                  << std::setw(12) << p.arrival_time
                  << std::setw(10) << p.burst_time
                  << std::setw(12) << p.completion_time
                  << std::setw(12) << p.turnaround_time
                  << std::setw(10) << p.wait_time << std::endl;
        
        total_tat += p.turnaround_time;
        total_wt += p.wait_time;       
    }
    std::cout << "\nAverage Turnaround Time: " << total_tat / process.size() << std::endl;
    std::cout << "Average Waiting Time: " << total_wt / process.size() << std::endl;
}
//============================ Space for main function only ===============================//

int main() {
    // asking the number of processes from the user
    std::cout<<"Enter the number of process"<< std::endl;
    int number_process;
    if(number_process <= 0) {
        std::cout<<"THE NUMBER OF PROCESS IS NOT VALID"<<"\n";
        exit(EXT_FAILURE);
    }

    std::vector<Process> process;

    for (int i = 0; i < number_process; i++) {
        int pid, priority;
        float arrival, burst;
        
        std::cout << "\nEnter details for Process " << (i + 1) << ":\n";
        std::cout << "PID: ";
        std::cin >> pid;
        std::cout << "Priority (lower number = higher priority): ";
        std::cin >> priority;
        std::cout << "Arrival Time: ";
        std::cin >> arrival;
        std::cout << "Burst Time: ";
        std::cin >> burst;
        
        Process p;
        p.pid = pid;
        p.priority = priority;
        p.arrival_time = arrival;
        p.burst_time = burst;
        p.completion_time = 0;
        p.turnaround_time = 0;
        p.wait_time = 0;

        process.push_back(p);
    }

    exit(EXT_SUCCESS);
}
