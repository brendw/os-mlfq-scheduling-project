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
    int getTimeRemaining();
    void decrementTimeRemaining(int);
    void updateWaitTime(int, int);
    void operator=(const Process &p);

};

Process::Process() {};

Process::Process(int arrival, int burst) {
    arrivalTime = arrival;
    totalBurstTime = burst;
    timeRemaining = burst;
    waitingTime = 0;
}
int Process::getTimeRemaining(){
    return timeRemaining;
}
void Process::decrementTimeRemaining(int burst) {
    timeRemaining -= burst;
}
void Process::updateWaitTime(int arrivalTime, int sentToCPUTime) {
    waitingTime += sentToCPUTime - arrivalTime; 
}
void Process::operator=(const Process &p) {
    arrivalTime = p.arrivalTime;
    timeRemaining = p.timeRemaining;
    totalBurstTime = p.totalBurstTime;
    waitingTime = p.waitingTime;
    turnaroundTime = p.turnaroundTime;
}

#endif 
