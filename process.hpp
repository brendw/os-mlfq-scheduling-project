#ifndef PROCESS_HPP
#define PROCESS_HPP

class Process {

int arrivalTime; //first arrives to RR queue1
int arrivalTime2; //arrives to q2/q3
int timeRemaining;
int waitingTime;
int turnaroundTime;
int startWaitingClock;
int finishedTime;  

public:
    int totalBurstTime;
    Process();
    Process(int, int);
    //void operator=(const Process &p);

    int getRemainingTime();
    void decrementTimeRemaining(int); //used in cpu 
    bool getFinished();
    
    void addWaitTime(int, int);
    int getWaitTime();

    void setFinishedTime(int);
    int getFinishedTime();

    int getArrivalTime();
    void setSecondArrivalTime(int);
    int getSecondArrivalTime();
};

#endif 
