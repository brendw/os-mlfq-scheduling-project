#include "cpu.hpp"
#include <iostream>

CPU::CPU() {
    resetFinishedTime(); 
}

Process CPU::runTask(Process p, int quantum, int currentClock) {

    int remainingTime = p.getRemainingTime();

    if (remainingTime > quantum) {
        p.decrementTimeRemaining(quantum);
        finishedTime = currentClock + quantum;
    }
    else {
        p.decrementTimeRemaining(remainingTime); //remaining is 0 
        finishedTime = currentClock + remainingTime;
    }
    p.setFinishedTime(finishedTime);
    return p; 

}
int CPU::getFinishedTime() {
    return finishedTime;
}

bool CPU::isBusy(int currentClock) {
    if (finishedTime == currentClock) {
        resetFinishedTime();
    }
    
    bool busy = true ? currentClock < finishedTime : false;
    std::cout << "-" << busy << std::endl;
    return busy;
}
void CPU::resetFinishedTime() {
    finishedTime = -1;
}