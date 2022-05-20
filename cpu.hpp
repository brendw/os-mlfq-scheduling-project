#ifndef CPU_HPP
#define CPU_HPP

#include "process.hpp"

class CPU {

int finishedTime; 
bool currentlyBusy; 
Process currentProcess;

public:
    CPU(); //constructor
    void runTask(Process, int, int);
    int getFinishedTime();
    bool isBusy(int); 
    void resetFinishedTime(); 
    Process returnProcess(int);
};

#endif