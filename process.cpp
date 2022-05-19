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