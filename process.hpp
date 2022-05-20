#ifndef PROCESS_HPP
#define PROCESS_HPP

class Process {

int arrivalTime;
int timeRemaining;
int waitingTime;
int turnaroundTime;

public:
    int totalBurstTime;
    Process();
    Process(int, int);
    int getRemainingTime();
    int getArrivalTime();
    void decrementTimeRemaining(int);
    void updateWaitTime(int, int);
    void operator=(const Process &p);

};

#endif 
