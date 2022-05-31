#include "cpu.hpp"
#include <iostream>

CPU::CPU() {
    resetFinishedTime();
    currentlyBusy = false; 
}

void CPU::runTask(Process p, int quantum, int currentClock) {

    // takes a process and the time it is allowed to run for
    // takes current click tick to calculate at which clock tick in future the process will be done

    currentProcess = p; // set p as CPU's attribute 
    int remainingTime = p.getRemainingTime();
    currentlyBusy = true; // CPU now busy with a process

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
        currentlyBusy = false; //CPU no longer busy now that process completed
        resetFinishedTime();
        return currentProcess;
    }
    else {
        Process p(-1, -1);  //current process not complete, return a null process 
        return p; 
    }
}