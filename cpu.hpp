#ifndef CPU_HPP
#define CPU_HPP

#include "process.hpp"

class CPU {

int finishedTime;
int remainingQuantum;
Process currentProcess;
bool hasProcess;

public:
    CPU(); //constructor
    void insertTask(Process, int);
    void runTask(int);
    bool endOfTask();
    Process relinquishProcess();

    int getFinishedTime();
    bool isBusy();
    bool isBusy(int); 
    void resetFinishedTime(); 
};

#endif