#include "scheduler.hpp"
#include <iostream>

//Scheduler::Scheduler(std::vector<int> arrival_times, std::vector<int> burst_times) { //constructor
//    // queues are already empty
//    RRquantum = 10; 
//    qc = 0;
//    arrivalTimes = arrival_times;
//    burstTimes = burst_times;
//
//    createProcessesList(arrival_times, burst_times); 
//}

Scheduler::Scheduler(std::vector<Process> processList, Policy* p) {
    this->processList = processList;
    this->schedulePolicy = p;

    this->RRquantum = p->getFirstQuantum();
    this->qc = 0;
}

//void Scheduler::createProcessesList(std::vector<int> arrival_times, std::vector<int> burst_times) {
//
//    for (int i = 0 ; i < arrival_times.size() ; i++) {
//
//        Process p(arrival_times[i], burst_times[i]); //create process with time attributes
//        processList.push(p);                   //add to list 
//    }
//}

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
            //processList.pop();
            processList.erase(processList.begin());
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

    int tasksRemainingCount = processList.size();
    // deal with queue1 arrivals and RR 
    while (tasksRemainingCount > 0 ) {
        std::cout << "Current clock: " << clock << std::endl;

        if (processList.size() != 0 && clock == processList.front().getArrivalTime()) {
            while (processList.size() != 0 && clock == processList.front().getArrivalTime()) {
                std::cout << "A process has arrived and been inserted into queue 1 at clock " << clock << std::endl;
                enqueueProcess(dequeueProcess(0), 1); //dequeue from processlist and add to queue1 
            }
        }

        //if the cpu is busy, just let it do its shit
        if (cpu.isBusy()) {
            //run the task
            cpu.runTask(clock);

            //check if the current task processing has ended
            if (cpu.endOfTask()) {
                //std::cout << "Task has ended" << std::endl;
                Process returnedProcess = cpu.relinquishProcess();
                tasksRemainingCount--;

                //check if this task is done
                if (returnedProcess.getFinished()) {
                    //do stuff
                    std::cout << "Returned process completed at clock " << clock << std::endl;
                    returnedProcess.setFinishedTime(clock);
                    wt.push_back(returnedProcess.getWaitTime());
                    tt.push_back(returnedProcess.getFinishedTime() - returnedProcess.getArrivalTime());
                }
                else {
                    //push this process somewhere else
                    std::cout << "Returned process being inserted into q2q3 process queue at clock " << clock << std::endl;
                    returnedProcess.setSecondArrivalTime(clock);
                    enqueueProcess(returnedProcess, 4);
                }
            }
            //else std::cout << "Task has not ended" << std::endl;
        } else if (queue1.size() != 0) { //if there are tasks to run in queue 1, grab one and feed it to the cpu
            //get the next task
            Process readyP = dequeueProcess(1);
            readyP.addWaitTime(clock, 1);
            //feed this process to the cpu
            cpu.insertTask(readyP, 10);
            std::cout << "Inserting a new process at clock " << clock << std::endl;
            cpu.runTask(clock);
        }
        //else if (queue2.size() != 0) { //if there are tasks to run in queue 2, grab one and feed it to the cpu

        //}
        //else if (queue3.size() != 0) { //if there are tasks to run in queue 3, grab one and feed it to the cpu

        //}

        //if (queue1.size() != 0 && !cpu.isBusy(clock)) {

        //    Process readyP = dequeueProcess(1);
        //    readyP.addWaitTime(clock, 1); 
        //    Process queue1CPUReturn = cpu.runTask(readyP, RRquantum, clock); // send first arrived process to CPU
        //    --tasksRemainingCount;

        //    int extraTime = queue1CPUReturn.getRemainingTime();
        //    if (extraTime > 0) {
        //        enqueueProcess( queue1CPUReturn, 4 ); //processes that exceed RR quantum are placed on this to calculate ratio for q2 and q3
        //    }
        //    else {
        //        //record wt and tt for completed processes
        //        wt.push_back(queue1CPUReturn.getWaitTime()); 
        //        tt.push_back(queue1CPUReturn.getFinishedTime()-queue1CPUReturn.getArrivalTime());    
        //    }
        //}
        clock++;
    }

    std::cout << "Finished queue 1 processing" << std::endl;

    //find percentile of qc_queue (already sorted) and place processes onto queues2&3
    moveQCQueueToQ23(clock);

    // deal with queue2 and queue3
    int q2_counter = 0; 
    //cpu.resetFinishedTime(); 

    while (cpu.isBusy() || queue2.size() != 0 || queue3.size() != 0) {
    //while (!cpu.isBusy() && queue2.size() > 0 && queue3.size() > 0) {
        //std::cout << clock << std::endl;
        std::cout << "Current clock: " << clock << std::endl;
        
        // deal with q2 & q3 -> send sjf to cpu
        int chosenQueue; 

        if (queue2.size() == 0) {
            chosenQueue = 3;
        }
        else if (queue3.size() == 0) {
            chosenQueue = 2;
        }
        else if (q2_counter < 3) {
            chosenQueue = 2;
        }
        else if (q2_counter == 3) {
            chosenQueue = 3;
        }

        if (cpu.isBusy()) {
            //run the task
            cpu.runTask(clock);

            if (cpu.endOfTask()) {
                Process returnedProcess = cpu.relinquishProcess();
                //tasksRemainingCount--;

                std::cout << "Returned process completed at clock " << clock << std::endl;
                returnedProcess.setFinishedTime(clock);
                wt.push_back(returnedProcess.getWaitTime());
                tt.push_back(returnedProcess.getFinishedTime() - returnedProcess.getArrivalTime());

                //check if this task is done
                //if (returnedProcess.getFinished()) {
                //    //do stuff
                //    std::cout << "Returned process completed at clock " << clock << std::endl;
                //    returnedProcess.setFinishedTime(clock);
                //}
                //else {
                //    //push this process somewhere else
                //    std::cout << "Returned process being inserted into q2q3 process queue at clock " << clock << std::endl;
                //    enqueueProcess(returnedProcess, 4);
                //}
            }
        }
        else {
            Process newProcess = dequeueProcess(chosenQueue);
            newProcess.addWaitTime(clock, 2);
            cpu.insertTask(newProcess, 99999999);
            if (chosenQueue == 2) {
                q2_counter++;
            }
            else if (chosenQueue == 3) {
                q2_counter = 0;
            }
            std::cout << "Inserting a new process at clock " << clock << std::endl;
            cpu.runTask(clock);
        }

        //if (!cpu.isBusy(clock)) {

        //    Process p = dequeueProcess(chosenQueue);
        //    p.addWaitTime(clock, chosenQueue);

        //    //Process returnedTask = cpu.runTask(p, p.getRemainingTime() , clock); // send shortest job to CPU

        //    //record wt and tt for completed processes
        //    //wt.push_back(returnedTask.getWaitTime()); 
        //    //tt.push_back(returnedTask.getFinishedTime()-returnedTask.getArrivalTime());    
        //}
        clock++; 
    }
} //end runScheduler

void Scheduler::runSchedulerNew() {
    int clock = 0; //start the clock 
    CPU cpu; //instantiate CPU

    int tasksRemainingCount = processList.size();
    bool ranTaskOnClock = false;

    while (tasksRemainingCount > 0) { //we'll find some ending condition in a bit
        ranTaskOnClock = false;
        for (Process p : processList) { //search through the process list for any processes that are arriving
            if (p.getArrivalTime() == clock) {
                std::cout << "A process " << p.getName() << " has arrived and been inserted into queue 1 at clock " << clock << std::endl;
                p.setPriorityLevel(1);
                enqueueProcess(p, 1);
            }
        }

        //if the cpu is busy, just let it do its shit

        if (cpu.isBusy()) {
            //run the task
            if (!cpu.endOfTask()) {
                cpu.runTask(clock);
                ranTaskOnClock = true;
            }

            //check if the current task processing has ended
            if (cpu.endOfTask()) {
                //std::cout << "Task has ended" << std::endl;
                Process returnedProcess = cpu.relinquishProcess();
                //check if the task is done
                bool isDone = returnedProcess.getFinished();
                if (isDone) {
                    std::cout << "Returned process " << returnedProcess.getName() << " completed at clock " << clock << std::endl;
                    returnedProcess.setFinishedTime(clock);
                    wt.push_back(returnedProcess.getWaitTime());
                    tt.push_back(returnedProcess.getFinishedTime());
                    tasksRemainingCount--;
                }
                else {
                    //push this process somewhere else
                    int newPriority = schedulePolicy->getNewPriorityForProcess(returnedProcess);
                    returnedProcess.setPriorityLevel(newPriority);
                    //returnedProcess.setArrivalTimeNew(clock);
                    returnedProcess.setSecondArrivalTime(clock);
                    std::cout << "Returned process " << returnedProcess.getName() << " being inserted into queue " << newPriority << " at clock " << clock << std::endl;
                    enqueueProcess(returnedProcess, newPriority);
                }
            }
            //else std::cout << "Task has not ended" << std::endl;
        }
        //else {
        if (!cpu.isBusy() && tasksRemainingCount > 0 && !ranTaskOnClock) {
            QueueStatus status = getQueueStatus();
            int nextQueueNumber = schedulePolicy->getNextQueue(status);
            Process readyP = dequeueProcess(nextQueueNumber);
            //readyP.addWaitTime(clock, 1); TODO: fix wait time
            if (nextQueueNumber == 1) {
                readyP.addWaitTime(clock, 1);
            }
            else {
                readyP.addWaitTime(clock, 2);
            }
            //readyP.addWaitTimeNew(clock);
            //feed this process to the cpu
            int readyProcessPriority = readyP.getPriorityLevel();
            //int quantumFromPolicy = schedulePolicy.getFirstQuantum(readyProcessPriority);
            int quantumFromPolicy = schedulePolicy->getQuantum(readyProcessPriority);
            cpu.insertTask(readyP, quantumFromPolicy);
            std::cout << "Inserting a new process " << readyP.getName() << " at clock " << clock << std::endl;
            cpu.runTask(clock);
            //insertedTaskOnClock = true;
        }
        clock++;
    }
}

void Scheduler::moveQCQueueToQ23(int clock){

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
}

void Scheduler::printBenchMarks() {

    int aveWT = 0;
    int aveTT = 0;

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

}

QueueStatus Scheduler::getQueueStatus() {
    int firstQueueLength = queue1.size();
    int secondQueueLength = queue2.size();
    int thirdQueueLength = queue3.size();

    QueueStatus returnValue(firstQueueLength, secondQueueLength, thirdQueueLength);
    return returnValue;
}