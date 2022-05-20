#include "cpu.hpp"

CPU::CPU() {
    currentTaskBurstTime; 
}

Process CPU::runTask(Process p, int quantum) {

    currentTaskBurstTime = p.getRemainingTime();

    int remainingTime = p.getRemainingTime();

    if (remainingTime > quantum) {
        p.decrementTimeRemaining(quantum);
    }
    else {
        p.decrementTimeRemaining(remainingTime); //remaining is 0 
    }
    
    return p; 

}
int CPU::getCurrentTaskBurstTime() {
    return currentTaskBurstTime;
}

bool CPU::isBusy(){
    if (currentTaskBurstTime>0) 
        return true;
}