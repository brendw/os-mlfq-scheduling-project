#include <iostream>
#include "scheduler.hpp"

int main(void) {

    // replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {1,2,3};
    std::vector<int> burst_times {6,7,8};


    Scheduler scheduler(arrival_times, burst_times); 
    scheduler.runScheduler();
    scheduler.printBenchMarks(); 

    return 0;
}