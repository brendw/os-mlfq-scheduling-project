#include <iostream>
#include "scheduler.hpp"

int main(void) {

    // replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {0,2,3,8,19,33,34};
    std::vector<int> burst_times {8,21,133,39,67,114,54};

    Scheduler scheduler(arrival_times, burst_times); 
    scheduler.runScheduler();
    scheduler.printBenchMarks(); 

    return 0;
}