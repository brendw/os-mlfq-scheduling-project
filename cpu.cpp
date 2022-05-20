#include "cpu.hpp"
#include <iostream>

CPU::CPU() {
    resetFinishedTime();
    currentlyBusy = false; 
}

void CPU::runTask(Process p, int quantum, int currentClock) {

    currentProcess = p; 
    int remainingTime = p.getRemainingTime();
    currentlyBusy = true;

    if (remainingTime > quantum) {
        currentProcess.decrementTimeRemaining(quantum);
        remainingTime -= quantum;
        finishedTime = currentClock + quantum;
    }
    else {
        currentProcess.decrementTimeRemaining(remainingTime); //remaining is 0 
        finishedTime = currentClock + remainingTime;
    }
    currentProcess.setFinishedTime(finishedTime);
}

int CPU::getFinishedTime() {
    return finishedTime;
}

bool CPU::isBusy(int currentClock) {

    bool busy = true ? currentClock < finishedTime : false;
    currentlyBusy = busy;
    std::cout << " - busy: " << busy << std::endl;
    return busy;
}
void CPU::resetFinishedTime() {
    finishedTime = -1;
}

Process CPU::returnProcess(int returnTime) {
    if (finishedTime == returnTime) {
        currentlyBusy = false;
        resetFinishedTime();
        return currentProcess;
    }
    else {
        Process p(-1, -1);
        return p; 
    }
}