#include <algorithm>
#include "policy.hpp"

Policy::Policy() {}

Policy::Policy(std::vector<Process> processList) {

}

//virtual int Policy::getNextQueue(QueueStatus status) { return 1; }
//
//int Policy::getFirstQuantum() { return firstQueueQuantum; };
//
//int Policy::getQuantum(int priorityLevel) { return 1; };
//
//int Policy::getNewPriorityForProcess(Process p) { return 1; };

PaperPolicy::PaperPolicy(std::vector<Process> processList) {
	this->processList = processList;
	int numLongProcessBursts = 0;
	std::vector<Process> largerProcessList;
	for (Process p : processList) {
		int processBurstTime = p.getTotalBurstTime();
		if (processBurstTime > 10) {
			//sumLongProcessBursts += processBurstTime;
			//numLongProcessBursts++;
			largerProcessList.push_back(p);
			
		}
	}

	/*bool compareProcesses(Process p1, Process p2) {
		int i1 = p1.getTotalBurstTime();
		int i2 = p2.getTotalBurstTime();
		return (i1 < i2);
	};*/

	auto compareProcesses = [](Process p1, Process p2) {
		int i1 = p1.getTotalBurstTime();
		int i2 = p2.getTotalBurstTime();
		return (i1 < i2);
	};

	//sort largerProcessList so we can find our 3/4 quantum
	std::sort(largerProcessList.begin(), largerProcessList.end(), compareProcesses);
	numLongProcessBursts = largerProcessList.size();
	
	//int adaptiveQuantum = sumLongProcessBursts / numLongProcessBursts;
	int percentileIndex = numLongProcessBursts * 3 / 4;
	int adaptiveQuantum = largerProcessList.at(percentileIndex).getTotalBurstTime();
	this->otherQueueQuantum = adaptiveQuantum;
	this->firstQueueQuantum = 10;
	agingFactor = 0;
}



int PaperPolicy::getNextQueue(QueueStatus status) {
	if (status.getFirstQueueCount() > 0) {
		return 1;
	}

	if (agingFactor >= 3 && status.getThirdQueueCount() > 0) {
		agingFactor = 0;
		return 3;
	}

	agingFactor = agingFactor + 1;
	return 2;
}

int PaperPolicy::getFirstQuantum() {
	return firstQueueQuantum;
}

int PaperPolicy::getQuantum(int queueNumber) {
	if (queueNumber == 1) {
		return firstQueueQuantum;
	}
	return 999999999;
}

int PaperPolicy::getNewPriorityForProcess(Process p) {
	int totalBurstForProcess = p.getTotalBurstTime();
	if (totalBurstForProcess > otherQueueQuantum) {
		return 3;
	}
	return 2;
}

BasePolicy::BasePolicy(std::vector<Process> processList) {

}

OurPolicy::OurPolicy(std::vector<Process> processList) {

}