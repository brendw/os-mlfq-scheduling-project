#include "cpu.hpp"

CPU::CPU() {
    resetFinishedTime(); 
}

Process CPU::runTask(Process p, int quantum, int currentClock, int queue) {

    p.updateWaitTime(currentClock, queue);

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
// int CPU::getFinishedTime() {
//     return finishedTime;
// }

bool CPU::isBusy(int currentClock) {
    return true ? currentClock < finishedTime : false;
}
void CPU::resetFinishedTime() {
    finishedTime = -1;
}