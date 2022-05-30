#include "process.hpp"

Process::Process() {};

Process::Process(int arrival, int burst) {
    arrivalTime = arrival;

    totalBurstTime = burst;
    timeRemaining = burst;
    waitingTime = 0;
    startWaitingClock = 0; 
}
// void Process::operator=(const Process &p) {
//     arrivalTime = p.arrivalTime;
//     timeRemaining = p.timeRemaining;
//     totalBurstTime = p.totalBurstTime;
//     waitingTime = p.waitingTime;
//     turnaroundTime = p.turnaroundTime;
// }

int Process::getRemainingTime(){
    return timeRemaining;
}
void Process::decrementTimeRemaining(int burst) {
    timeRemaining -= burst;
}

bool Process::getFinished() {
    return timeRemaining == 0;
}

void Process::addWaitTime(int clock, int whichArrival) {

    if (whichArrival == 1)
        waitingTime += clock - arrivalTime;
    else
        waitingTime += clock - arrivalTime2;
}

void Process::addWaitTimeNew(int clock) {
    waitingTime += clock - arrivalTime;
}

int Process::getWaitTime() {
    return waitingTime; 
}

void Process::setFinishedTime(int time) {
    finishedTime = time;
}
int Process::getFinishedTime() {
    return finishedTime;
}

int Process::getArrivalTime(){
    return arrivalTime;
}
void Process::setSecondArrivalTime(int clock) { //when processes are requeued to q2/q3
    arrivalTime2 = clock;
}
int Process::getSecondArrivalTime() {
    return arrivalTime2;
}

void Process::setArrivalTimeNew(int clock) {
    arrivalTime = clock;
}

int Process::getTotalBurstTime() {
    return totalBurstTime;
}

int Process::getPriorityLevel() {
    return priorityLevel;
}

void Process::setPriorityLevel(int level) {
    priorityLevel = level;
}
