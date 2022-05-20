#include "process.hpp"

Process::Process() {};

Process::Process(int arrival, int burst) {
    arrivalTime = arrival;
    totalBurstTime = burst;
    timeRemaining = burst;
    waitingTime = 0;
}
int Process::getRemainingTime(){
    return timeRemaining;
}
int Process::getArrivalTime(){
    return arrivalTime;
}
void Process::decrementTimeRemaining(int burst) {
    timeRemaining -= burst;
}
void Process::updateWaitTime(int arrivalTime, int sentToCPUTime) {
    waitingTime += sentToCPUTime - arrivalTime; 
}
void Process::operator=(const Process &p) {
    arrivalTime = p.arrivalTime;
    timeRemaining = p.timeRemaining;
    totalBurstTime = p.totalBurstTime;
    waitingTime = p.waitingTime;
    turnaroundTime = p.turnaroundTime;
}