#include "process.cpp"

class CPU {

int clock;

public:
    CPU(); //constructor
    Process runTask(Process, int);
};

CPU::CPU() {
    clock = 0; //?
}

Process runTask(Process p, int quantum) {

    int remainingTime = p.getTimeRemaining();

    if (remainingTime > quantum) {
        p.decrementTimeRemaining(quantum);
    }
    else {
        p.decrementTimeRemaining(remainingTime); //remaining is 0 
    }
    
    return p; 

}