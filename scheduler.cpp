#include "scheduler.hpp"
#include <iostream>

Scheduler::Scheduler(std::vector<int> arrival_times, std::vector<int> burst_times) { //constructor
    // queues are already empty
    RRquantum = 10; 
    qc = 0;
    arrivalTimes = arrival_times;
    burstTimes = burst_times;

    createProcessesList(arrival_times, burst_times); 
}

void Scheduler::createProcessesList(std::vector<int> arrival_times, std::vector<int> burst_times) {

    for (int i = 0 ; i < arrival_times.size() ; i++) {

        Process p(arrival_times[i], burst_times[i]); //create process with time attributes
        processList.push(p);                   //add to list 
    }
}

void Scheduler::enqueueProcess(Process p, int queueNumber) {
    switch (queueNumber) {
        case 1:
            queue1.push(p);
            break;
        case 2:
            queue2.push(p);
            break;
        case 3:
            queue3.push(p);
            break;
        case 4:
            qc_queue.push(p);
    }
}
Process Scheduler::dequeueProcess(int currentQueue) {
    //dequeue the first process to send to CPU
    Process removedProcess;
    switch (currentQueue) {
        case 0:
            removedProcess = processList.front();
            processList.pop();
            break;
        case 1:
            removedProcess = queue1.front();
            queue1.pop();
            break;
        case 2:
            removedProcess = queue2.top(); 
            queue2.pop(); //remove top element
            break;
        case 3:
            removedProcess = queue3.top();
            queue3.pop(); //remove top element 
            break;
        case 4:
            removedProcess = qc_queue.top();
            qc_queue.pop();
            break;
    }
    return removedProcess;
}

void Scheduler::runScheduler() {

    int clock = 0; //start the clock 
    CPU cpu; //instantiate CPU 

    int tasksRemaining = processList.size(); //loop with clock running until all processes have gone through q1 

    // deal with queue1 arrivals and RR 
    while (tasksRemaining > 0 ) {
        std::cout << clock;

        // 1) enqueue any arriving processes onto queue1    
        while (processList.size() != 0 && clock == processList.front().getArrivalTime() ) {

            enqueueProcess( dequeueProcess(Q0), Q1 ); //dequeue from processlist and add to queue1 
        }

        // 2) check if there's a returning process from CPU
        Process queue1CPUReturn = cpu.returnProcess(clock); //return from CPU;
        
        if (queue1CPUReturn.getArrivalTime() != -1) { //valid process returned
            std::cout << "process returned from CPU" << std::endl;
            int extraTime = queue1CPUReturn.getRemainingTime();
            if (extraTime > 0) {
                enqueueProcess( queue1CPUReturn, QC ); //processes that exceed RR quantum are placed on this to calculate ratio for q2 and q3
            }
            else {
                //record wt and tt for completed processes
                wt.push_back(queue1CPUReturn.getWaitTime()); 
                tt.push_back(queue1CPUReturn.getFinishedTime()-queue1CPUReturn.getArrivalTime());    
            }
            --tasksRemaining;
        } //else a process did not return 

        // 3) send ready process to CPU if free
        if (queue1.size() != 0 && !cpu.isBusy(clock)) {

            Process readyP = dequeueProcess(Q1); // get process at front of q1 (RR/FIFO)
            readyP.addWaitTime(clock, 1);       // record its wait time
            cpu.runTask(readyP, RRquantum, clock); // send to CPU to run for the RR time quantum 
        } 

        clock++;
        std::cout<<std::endl;
    } // while tasksRemaining

    --clock; //clock is incremented at last loop when q1 completes, decrement it

    moveQCQueueToQ23(clock);  //find percentile of qc_queue (already sorted) and place processes onto queues2&3

    // deal with queue2 and queue3
    tasksRemaining = queue2.size() + queue3.size(); //loop with clock running until all processes have gone through q2/q3

    while (tasksRemaining) { 
        std::cout << clock; 
        
        // 1) check if there's a return process from CPU
        Process returnP = cpu.returnProcess(clock); //return from CPU;
        
        if (returnP.getArrivalTime() != -1) { //valid process returned
            std::cout << "process returned from CPU" << std::endl;
            //record wt and tt for completed processes
            wt.push_back(returnP.getWaitTime()); 
            tt.push_back(returnP.getFinishedTime()-returnP.getArrivalTime());    
            --tasksRemaining;
        } //else a process did not return 

        
        // 2) send ready process to CPU if free
        if ((queue2.size() != 0 || queue3.size() ) && !cpu.isBusy(clock)) {

            int chosenQueue = chooseQueue(); // pick whether process comes from q2 or q3 for cpu

            Process readyP = dequeueProcess(chosenQueue); //get process at front of sorted by time remaining queue
            readyP.addWaitTime(clock, chosenQueue);       //record its wait time

            cpu.runTask(readyP, readyP.getRemainingTime() , clock); // send shortest job to CPU and run to completion 
        }

        clock++; 
        std::cout<<std::endl;
    } //end tasksRemaininging on q2/q3
} //end runScheduler

void Scheduler::moveQCQueueToQ23(int clock){

    //find percentile of qc_queue (already sorted) and place processes onto queues2&3
    int percentile_index = qc_queue.size() * 3/4; 
    int percentile_time;

    if (qc_queue.size() != 0) {

        for (int i = 0 ; i <= percentile_index ; i++ ) {
            
            Process p = dequeueProcess(QC);

            if ( i == percentile_index) {
                percentile_time = p.getRemainingTime();
            }
            p.setSecondArrivalTime(clock);
            enqueueProcess( p , Q2 ); //pop from qc_queue and enqueue on queue2
        }

        for (int i = 0 ; i<qc_queue.size() ; i++) { //whatever is left on qc_queue goes to queue3
            Process p = dequeueProcess(QC);
            p.setSecondArrivalTime(clock);
            enqueueProcess(p, Q3); 
        }
    }
}
int Scheduler::chooseQueue() {

    int ratio = 4; // ratio is X:1 for Q2 to Q3

    static int q2_counter = 0; 

    int chosenQueue;
    if (queue2.size() == 0) { //Q2 is empty so place in Q3
        chosenQueue = 3;
    }
    else if (queue3.size() == 0) { //Q3 is empty so place in Q2
        chosenQueue = 2; 
    }
    else if (q2_counter < ratio) { //ratio placed in Q2
        chosenQueue = 2;
        ++q2_counter;
    }
    else if (q2_counter == ratio) { //ratio placed in Q3 
        chosenQueue = 3;
        q2_counter = 0; //reset counter
    } 
    return chosenQueue;

}

void Scheduler::printBenchMarks() {

    int aveWT, aveTT;

    int totalCount = wt.size();

    for (auto &time : wt) {
        aveWT += time;
    }
    aveWT /= (float) totalCount;

    for (auto &time : tt) {
        aveTT += time;
    }
    aveTT /= (float) totalCount;

    std::cout << "average wait time = " << aveWT << std::endl;
    std::cout << "average turnaround time = " << aveTT << std::endl;
    std::cout << std::endl;

}