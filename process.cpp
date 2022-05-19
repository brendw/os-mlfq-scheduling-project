class Process {

int arrivalTime;
int timeRemaining;
int waitingTime;

public:
    int totalBurstTime;
    Process();
    Process(int, int);
    int getTimeRemaining();
    void decrementTimeRemaining(int);

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