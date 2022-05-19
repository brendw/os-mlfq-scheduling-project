#include <iostream>
#include "process.cpp"
#include "scheduler.cpp"
#include "cpu.cpp"
#include <queue>

int main(void) {

    // replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {1,2,3};
    std::vector<int> burst_times {6,7,8};


    Scheduler scheduler(arrival_times, burst_times); 
    CPU cpu; //?

    scheduler.runScheduler();
    

    return 0;
}