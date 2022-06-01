#include "cpu.hpp"
#include <iostream>

CPU::CPU() {
    resetFinishedTime(); 
    hasProcess = false;
}

//Process CPU::runTask(Process p, int quantum, int currentClock) {
//
//    int remainingTime = p.getRemainingTime();
//
//    if (remainingTime > quantum) {
//        p.decrementTimeRemaining(quantum);
//        finishedTime = currentClock + quantum;
//    }
//    else {
//        p.decrementTimeRemaining(remainingTime); //remaining is 0 
//        finishedTime = currentClock + remainingTime;
//    }
//    p.setFinishedTime(finishedTime);
//    return p; 
//
//}

void CPU::insertTask(Process newProcess, int quantumAvailable) {
    this->currentProcess = newProcess;
    this->hasProcess = true;
    this->remainingQuantum = quantumAvailable;
    std::cout << "CPU receives process with remaining burst of " << currentProcess.getRemainingTime() << " and time quantum of " << remainingQuantum << std::endl;
}

void CPU::runTask(int currentClock) { //i guess we have the current clock for debug purposes?
    this->currentProcess.decrementTimeRemaining(1);
    this->remainingQuantum--;

    //std::cout << "Running process at clock " << currentClock << ", remaining processing time: " << currentProcess.getRemainingTime() << ", remaining quantum: " << remainingQuantum << std::endl;
}

bool CPU::endOfTask() {
    if (currentProcess.getRemainingTime() == 0) {
        return true;
    }
    if (remainingQuantum == 0) {
        return true;
    }
    return false;
}

Process CPU::relinquishProcess() {
    Process p = currentProcess;
    hasProcess = false;
    return p;
}

int CPU::getFinishedTime() {
    return finishedTime;
}

bool CPU::isBusy() {
    //if (finishedTime == currentClock) {
    //    resetFinishedTime();
    //}
    //
    //bool busy = true ? currentClock < finishedTime : false;
    //std::cout << "-" << busy << std::endl;
    //return busy;

    return hasProcess;
 
}

bool CPU::isBusy(int currentClock) {
    if (finishedTime == currentClock) {
        resetFinishedTime();
    }
    bool busy = true ? currentClock < finishedTime : false;
    std::cout << "-" << busy << std::endl;
    return busy;

    //return hasProcess;

}
void CPU::resetFinishedTime() {
    finishedTime = -1;
}