#include <iostream>
#include "scheduler.hpp"

int main(void) {

    //replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {0,2,3,8,19,33,33};
    std::vector<int> burst_times {8,21,133,39,67,114,54};

    // std::vector<int> arrival_times {0,2,  3,  8, 10,19,21,26,  33,33,42,  88,92};
    // std::vector<int> burst_times   {8,21,133,39, 19,67,7,6,114,54,15,6,17 };

    Scheduler scheduler(arrival_times, burst_times); 
    scheduler.runScheduler();
    scheduler.printBenchMarks(); 

    return 0;
}