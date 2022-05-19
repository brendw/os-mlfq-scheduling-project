#include <iostream>
#include "process.cpp"
#include <vector>
#include <queue>

struct CompareProcesses{
    
    // the point is to have a smallest burst_time at the top of the queue
    bool operator()(Process const *p1, Process const *p2 ) {
        return (*p1).totalBurstTime > (*p2).totalBurstTime;
    }
};

class Scheduler { // MLFQ 

    std::queue<Process> queue1;
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> queue2;
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> queue3;
    int RRquantum;
    int qc; 
    std::vector<int> wt; //wait times = sentToCPUTime - arrival 
    std::vector<int> tt; //turnaround times = wt+burst time
    
public:
    Scheduler(); //constructor
    void enqueueProcess(Process, int);
    Process dequeueProcess(int);
    void runScheduler(std::queue<Process> processes);
    void addToQc(Process); 
};

Scheduler::Scheduler() {
    // empty queues 
    RRquantum = 10; 
    qc = 0;
}

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
    //dequeue the first process to send to CPU
    Process removedProcess;
    switch (currentQueue) {
        case 1:
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

void Scheduler::runScheduler(std::queue<Process> processes) {

    wt.reserve(processes.size());
    tt.reserve(processes.size());

    // deal with queue1

    // send first arrived process to CPU
    // dequeue
    // for any processes that returns incomplete, add time to qc
    addToQc(p);
    // send to either q2 or q3
    // enqueue(p, 2) or enqueue(p, 3)

    // deal with queue2
    // send sjf to cpu

    // deal with queue2
    // send sjf to cpu
}

void Scheduler::addToQc(Process p) {

    // if time remaining is 0, this won't affect qc
    qc += p.getTimeRemaining(); 

}