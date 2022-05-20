#include "scheduler.hpp"

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

    // deal with queue1 arrivals and RR 
    while (processList.size() != 0) {

        if (clock == processList.front().getArrivalTime()) {

            // KEEP TRACK OF WAIT TIME
            enqueueProcess( dequeueProcess(0), 1 ); //dequeue from processlist and add to queue1 
        }

        if (queue1.size() != 0 and not cpu.isBusy(clock)) {

            Process queue1CPUReturn = cpu.runTask(dequeueProcess(1), RRquantum, clock, 1); // send first arrived process to CPU
    
            int extraTime = queue1CPUReturn.getRemainingTime();
            if (extraTime > 0) {
                enqueueProcess( queue1CPUReturn, 4 ); //processes that exceed RR quantum are placed on this to calculate ratio for q2 and q3
            }
            else {
                //record wt and tt for completed processes
                wt.push_back(queue1CPUReturn.getWaitTime()); 
                tt.push_back(queue1CPUReturn.getFinishedTime()-queue1CPUReturn.getArrivalTime());    
            }
        }
        clock++;
    }

    //find percentile of qc_queue (already sorted) and place processes onto queues2&3
    int percentile_index = qc_queue.size() * 3/4; 
    int percentile_time;

    if (qc_queue.size() != 0) {

        for (int i = 0 ; i <= percentile_index ; i++ ) {
            
            Process p = dequeueProcess(4);

            if ( i == percentile_index) {
                percentile_time = p.getRemainingTime();
            }
            p.setSecondArrivalTime(clock);
            enqueueProcess( p , 2 ); //pop from qc_queue and enqueue on queue2
        }

        for (int i = 0 ; i<qc_queue.size() ; i++) { //whatever is left on qc_queue goes to queue3
            Process p = dequeueProcess(4);
            p.setSecondArrivalTime(clock);
            enqueueProcess(p, 3); 
        }
    }
    // deal wtih queue2 and queue3
    int q2_counter = 0; 
    cpu.resetFinishedTime(); 

    while (queue2.size() != 0 or queue3.size() != 0) {
        
        // deal with q2 & q3 -> send sjf to cpu

        int chosenQueue; 

        if (queue2.size() == 0) {
            chosenQueue = 3;
        }
        else if (queue3.size() == 0) {
            chosenQueue = 2; 
        }
        else if (q2_counter++ < 3) {
            chosenQueue = 2;
        }
        else if (q2_counter == 3) {
            chosenQueue = 3;
            q2_counter = 0; 
        }

        if (not cpu.isBusy(clock)) {

            Process p = dequeueProcess(chosenQueue);

            Process returnedTask = cpu.runTask(p, p.getRemainingTime() , clock, chosenQueue); // send shortest job to CPU

            //record wt and tt for completed processes
            wt.push_back(returnedTask.getWaitTime()); 
            tt.push_back(returnedTask.getFinishedTime()-returnedTask.getArrivalTime());    

        }

        clock++; 
    }
} //end runScheduler

void Scheduler::printBenchMarks() {

    int aveWT, aveTT;

    int totalCount = wt.size();

    for (auto &time : wt) {
        aveWT += time;
        std::cout << time << " "; 
    }
    std::cout << std::endl;
    aveWT /= (float) totalCount;

    for (auto &time : tt) {
        aveTT += time;
        std::cout << time << " ";
    }
    std::cout  << std::endl;
    aveTT /= (float) totalCount;

    std::cout << "average wait time = " << aveWT << std::endl;
    std::cout << "average turnaround time = " << aveTT << std::endl;

}