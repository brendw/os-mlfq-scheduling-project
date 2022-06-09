#include "scheduler.hpp"
#include <iostream>

Scheduler::Scheduler(std::vector<Process> processList, Policy* p) {
    this->processList = processList;
    this->schedulePolicy = p;

    this->RRquantum = p->getFirstQuantum();
    this->qc = 0;
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
            //processList.pop();
            processList.erase(processList.begin());
            break;
        case 1:
            removedProcess = queue1.front();
            queue1.pop();
            break;
        case 2:
            removedProcess = queue2.top(); 
            //removedProcess = queue2.front();
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

        //if the cpu is busy, just let it do its stuff

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
            //feed this process to the cpu
            int readyProcessPriority = readyP.getPriorityLevel();
            //int quantumFromPolicy = schedulePolicy.getFirstQuantum(readyProcessPriority);
            int quantumFromPolicy = schedulePolicy->getQuantum(readyProcessPriority);
            cpu.insertTask(readyP, quantumFromPolicy);
            std::cout << "Inserting a new process " << readyP.getName() << " at clock " << clock << std::endl;
            cpu.runTask(clock);
        }
        clock++;
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