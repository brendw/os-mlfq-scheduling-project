#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include "process.hpp"
#include "cpu.hpp"

enum queue { Q0=0, Q1=1, Q2=2, Q3=3, QC=4 }; 

struct CompareProcesses{
    // want smallest burst_time at the top of the queue
    bool operator()(const Process p1, const Process p2 ) {
        return p1.totalBurstTime > p2.totalBurstTime;
    }
};

class Scheduler { 

    // MLFQ
    std::queue<Process> queue1; // RR (FIFO but only 1 turn)
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> queue2; // SJF
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> queue3; // SJF
    int RRquantum;
    int qc; 
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> qc_queue; //processes that exceed RR timequantum
    
    // arriving processes to be scheduled and run
    std::vector<int> arrivalTimes;
    std::vector<int> burstTimes;
    
    void createProcessesList(std::vector<int>, std::vector<int>);
    std::queue<Process> processList;

    // benchmarks 
    std::vector<int> wt; //wait times = sentToCPUTime - arrival 
    std::vector<int> tt; //turnaround times = wt+burst time


public:
    Scheduler(std::vector<int>, std::vector<int>); //constructor
    void enqueueProcess(Process, int);
    Process dequeueProcess(int);
    void runScheduler();
    void moveQCQueueToQ23(int); //after q1 RR completes, place the remaining processes on q2 and q3 split at a percentile 
    int chooseQueue(); //determine whether a process from q2 or q3 gets sent to cpu
    void printBenchMarks();

}; //class Scheduler

#endif