#ifndef CPU_HPP
#define CPU_HPP

#include "process.hpp"

class CPU {

int finishedTime; 

public:
    CPU(); //constructor
    Process runTask(Process, int, int, int);
    int getFinishedTime();
    bool isBusy(int); 
    void resetFinishedTime(); 
};

#endif