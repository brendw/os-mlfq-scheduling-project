#include "scheduler.hpp"

Scheduler::Scheduler(std::vector<int> arrival_times, std::vector<int> burst_times) { //constructor
    // queues are already empty
    RRquantum = 10; 
    qc = 0;
    arrivalTimes = arrival_times;
    burstTimes = burst_times;
    wt.reserve(arrival_times.size());
    tt.reserve(arrival_times.size());

    createProcessesList(arrival_times, burst_times); 
}

void Scheduler::createProcessesList(std::vector<int> arrival_times, std::vector<int> burst_times) {

    for (int i = 0 ; i < arrival_times.size() ; i++) {

        Process p(arrival_times[i], burst_times[i]); //create process with time attributes
        processList.push(p);                   //add to list 
    }
    processesRemain = true;
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

    int clock = 0;

    CPU cpu; 

    int percentile; 

    while (processesRemain) {

        // deal with queue1
        if (clock == processList.front().getArrivalTime()) {

            // KEEP TRACK OF WAIT TIME
            enqueueProcess( dequeueProcess(0), 1 ); //dequeue from processlist and add to queue1 
        }

        if (queue1.size() != 0 and not cpu.isBusy()) {

            Process quantumExceededP = cpu.runTask(dequeueProcess(1), RRquantum); // send first arrived process to CPU

            int extraTime = quantumExceededP.getRemainingTime();

            if (extraTime > 0) {
                enqueueProcess( quantumExceededP, 4 ); //processes that exceed RR quantum are placed on this to calculate ratio for q2 and q3
                qc += extraTime; //record PROBS DONT NEED THIS
            }
        }

        // find percentile of qc_queue (already sorted)
        int percentile_index = qc_queue.size() * 3/4;  //CHECK THAT IT"S AN INTEGER
        int percentile_time;
        
        for (int i = 0 ; i <= percentile_index ; i++ ) {
            
            Process p = dequeueProcess(4);

            if ( i == percentile_index) {
                percentile_time = p.getRemainingTime();
            }
            enqueueProcess( p , 2 ); //pop from qc_queue and enqueue on queue2
        }

        queue3 = qc_queue; //whatever is left on qc_queue goes to queue3



        // send to either q2 or q3
        // enqueue(p, 2) or enqueue(p, 3)

        // deal with queue2
        // send sjf to cpu

        // deal with queue3
        // send sjf to cpu
        // if (queue3.size() == 0) processesRemaing = false;

        clock++;
    }


}