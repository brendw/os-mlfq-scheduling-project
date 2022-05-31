#include <algorithm>
#include <iostream>
#include "policy.hpp"

Policy::Policy() {}

Policy::Policy(std::vector<Process> processList) {}

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
	std::cout << "Adaptive quantum value: " << adaptiveQuantum << std::endl;
	this->otherQueueQuantum = adaptiveQuantum;
	this->firstQueueQuantum = 10;
	queueQuantums.push_back(10);
	queueQuantums.push_back(999999999);
	queueQuantums.push_back(999999999);
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
	//return firstQueueQuantum;
	return queueQuantums.at(0);
}

int PaperPolicy::getQuantum(int queueNumber) {
	int position = queueNumber - 1;
	return queueQuantums.at(position);
	//if (queueNumber == 1) {
	//	return firstQueueQuantum;
	//}
	//return 999999999;
}

int PaperPolicy::getNewPriorityForProcess(Process p) {
	int totalBurstForProcess = p.getTotalBurstTime();
	if (totalBurstForProcess > otherQueueQuantum) {
		return 3;
	}
	return 2;
}

BasePolicy::BasePolicy(std::vector<Process> processList) {
	this->processList = processList;
	this->queueQuantums.push_back(10);
	//this->otherQueueQuantum = 100;
	this->queueQuantums.push_back(50);
	this->queueQuantums.push_back(999999999);
}

int BasePolicy::getNextQueue(QueueStatus status) {
	if (status.getFirstQueueCount() > 0) {
		return 1;
	}
	else if (status.getSecondQueueCount() > 0) {
		return 2;
	}
	else return 3;
}

int BasePolicy::getFirstQuantum() {
	return queueQuantums.at(0);
}

int BasePolicy::getQuantum(int queueNumber) {
	int position = queueNumber - 1;
	return queueQuantums.at(position);
}

int BasePolicy::getNewPriorityForProcess(Process p) {
	int currentPriority = p.getPriorityLevel();
	if (currentPriority == 3) return 3;
	currentPriority++;
	return currentPriority;
}

OurPolicy::OurPolicy(std::vector<Process> processList) {

}

int OurPolicy::getNextQueue(QueueStatus status) {
	return 1;
}

int OurPolicy::getFirstQuantum() {
	return 0;
}

int OurPolicy::getQuantum(int queueNumber) {
	return 0;
}

int OurPolicy::getNewPriorityForProcess(Process p) {
	return 0;
}