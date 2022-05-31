#include <iostream>
#include "scheduler.hpp"

int main(void) {

    //replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {0,2,3,8,19,33,33};
    std::vector<int> burst_times {8,21,133,39,67,114,54};

    // std::vector<int> arrival_times {0,2,  3,  8, 10,19,21,26,  33,33,42,  88,92};
    // std::vector<int> burst_times   {8,21,133,39, 19,67,7,6,114,54,15,6,17 };

    Scheduler scheduler1(arrival_times, burst_times, 10, 3, 4, 3); 
    scheduler1.runScheduler();

    std::vector<int> burst_times2 {30,21,133,70,90,114,120};

    Scheduler scheduler2(arrival_times,burst_times2, 10, 3, 4, 3 );
    scheduler2.runScheduler();

    Scheduler scheduler3(arrival_times,burst_times, 10, 3, 5, 3 );
    scheduler3.runScheduler();

    Scheduler scheduler4(arrival_times,burst_times2, 10, 3, 5, 3 );
    scheduler4.runScheduler();

    scheduler1.printBenchMarks(); 
    scheduler2.printBenchMarks();
    scheduler3.printBenchMarks();
    scheduler4.printBenchMarks();



    return 0;
}