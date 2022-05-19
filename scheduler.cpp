#include <iostream>
#include "process.cpp"
#include <vector>
#include <queue>


struct CompareProcesses{
    
    // the point is to have a smallest burst_time at the top of the queue
    bool operator()(Process const *p1, Process const *p2 ) {
        return p1.burstTime > p2.burstTime;
    }
};

class Scheduler { // MLFQ 

    std::queue<Process> queue1;
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> queue2;
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> queue3;
    
public:
    //Scheduler(); //constructor
    void enqueueProcess(Process, int);
    Process dequeueProcess(int);
    std::queue<Process> createProcessList(std::vector<int>, std::vector<int>);
    void runScheduler();


};

// Scheduler::Scheduler() {
//     // empty queues
// }

void Scheduler::enqueueProcess(Process p, int queueNumber) {
    switch (queueNumber) {
        case 1:
            queue1.push(p);
            break;
        case 2:
            queue2.push(p);
            break;
        case 3:
            queue3.push(p);
            break;
    }
}
Process Scheduler::dequeueProcess(int currentQueue) {
    Process removedProcess;
    switch (currentQueue) {
        case 1:
            // process did not complete in queue1 RR quantum so will be moved to queue2 or queue3
            removedProcess = queue1.front();
            queue1.pop();
            break;
        case 2:
            removedProcess = queue2.top();
            queue2.pop();
            break;
        case 3:
            removedProcess = queue3.top();
            queue3.pop();
            break;
    }
    return removedProcess;
}

void Scheduler::runScheduler() {

    std::vector<int> arrival_times {1,2,3};
    std::vector<int> burst_time {6,7,8};

    // deal with queue1


    // deal with queue2


    // deal with queue2



}

std::queue<Process> createProcessList(std::vector<int> arrivalTimes, std::vector<int> burstTimes) {

    std::queue<Process> arrivingProcesses; 

    for (int i = 0 ; i < arrivalTimes.size() ; i++) {

        Process p(arrivalTimes[i], burstTimes[i]); //create process with attributes
        arrivingProcesses.push(p);                 //add to list 
    }

    return arrivingProcesses; 

}