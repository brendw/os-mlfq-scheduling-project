

class Process {

int totalTime;
int timeRemaining;

public:
    Process();
    Process(int);
    int getTimeRemaining();
    void decrementTimeRemaining(int);

};

Process::Process() {};

Process::Process(int time) {
    totalTime = time;
    timeRemaining =time;
}
int Process::getTimeRemaining(){
    return timeRemaining;
}
void Process::decrementTimeRemaining(int burst) {
    timeRemaining -= burst;
}