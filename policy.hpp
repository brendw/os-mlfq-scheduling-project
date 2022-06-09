#pragma once

#include <vector>
#include "process.hpp"
#include "queuestatus.hpp"

class Policy {
protected:
	std::vector<Process> processList;
	int firstQueueQuantum;
	int otherQueueQuantum;
	std::vector<int> queueQuantums;

public:
	Policy();
	Policy(std::vector<Process>);
	virtual int getNextQueue(QueueStatus) = 0;
	virtual int getFirstQuantum() = 0;
	virtual int getQuantum(int) = 0;
	virtual int getNewPriorityForProcess(Process) = 0;
};

class PaperPolicy : public Policy {

	std::vector<Process> mainProcesses;
	int agingFactor;
	//int dynamicQuantum;

public:
	PaperPolicy(std::vector<Process>);
	int getNextQueue(QueueStatus);
	int getFirstQuantum();
	int getQuantum(int);
	int getNewPriorityForProcess(Process);
};

class BasePolicy : public Policy {

public:
	BasePolicy(std::vector<Process>);
	int getNextQueue(QueueStatus);
	int getFirstQuantum();
	int getQuantum(int);
	int getNewPriorityForProcess(Process);
};

class OurPolicy : public Policy {

	std::vector<Process> mainProcesses;
	int agingFactor;

public:
	OurPolicy(std::vector<Process>);
	int getNextQueue(QueueStatus);
	int getFirstQuantum();
	int getQuantum(int);
	int getNewPriorityForProcess(Process);
};