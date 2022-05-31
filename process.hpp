#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>

class Process {
    std::string name;
    int arrivalTime; //first arrives to RR queue1
    
    int arrivalTime2; //arrives to q2/q3
    int timeRemaining;
    int waitingTime;
    int turnaroundTime;
    int startWaitingClock;
    int finishedTime;
    int priorityLevel;

public:
    int totalBurstTime;
    Process();
    Process(std::string, int, int);
    //void operator=(const Process &p);

    std::string getName();

    int getRemainingTime();
    void decrementTimeRemaining(int); //used in cpu 
    bool getFinished();
    
    void addWaitTime(int, int);
    void addWaitTimeNew(int);
    int getWaitTime();

    void setFinishedTime(int);
    int getFinishedTime();

    int getArrivalTime();
    void setSecondArrivalTime(int);
    int getSecondArrivalTime();
    int getTotalBurstTime();

    void setArrivalTimeNew(int);

    int getPriorityLevel();
    void setPriorityLevel(int);
};

#endif 
