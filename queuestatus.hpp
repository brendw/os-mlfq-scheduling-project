#pragma once

class QueueStatus {

	int firstQueueElements;
	int secondQueueElements;
	int thirdQueueElements;

public:
	QueueStatus(int, int, int);
	int getFirstQueueCount();
	int getSecondQueueCount();
	int getThirdQueueCount();
};