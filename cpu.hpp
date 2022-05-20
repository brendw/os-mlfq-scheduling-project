#ifndef CPU_HPP
#define CPU_HPP

#include "process.hpp"

class CPU {

int currentTaskBurstTime; 

public:
    CPU(); //constructor
    Process runTask(Process, int);
    int getCurrentTaskBurstTime();
};

#endif