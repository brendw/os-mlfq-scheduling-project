#include <iostream>
#include "scheduler.hpp"

int main(void) {

    // replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {0,3,2,8,19,33,33,};
    std::vector<int> burst_times {8,133,21,39,67,114,54,};

    Scheduler scheduler(arrival_times, burst_times); 
    scheduler.runScheduler();
    scheduler.printBenchMarks(); 

    return 0;
}