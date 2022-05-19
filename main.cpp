#include <iostream>
#include "process.cpp"
#include "scheduler.cpp"
#include "cpu.cpp"
#include <queue>

int main(void) {

    // replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {1,2,3};
    std::vector<int> burst_times {6,7,8};

    //create process list 
    std::queue<Process> arrivingProcesses; 
    for (int i = 0 ; i < arrival_times.size() ; i++) {

        Process p(arrival_times[i], burst_times[i]); //create process with attributes
        arrivingProcesses.push(p);                   //add to list 
    }

    // ---------------------------------------------------------
    
    Scheduler scheduler;
    CPU cpu; //?

    scheduler.runScheduler(arrivingProcesses);
    

    return 0;
}