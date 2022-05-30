#include "queuestatus.hpp"

QueueStatus::QueueStatus(int firstCount, int secondCount, int thirdCount) {
	this->firstQueueElements = firstCount;
	this->secondQueueElements = secondCount;
	this->thirdQueueElements = thirdCount;
}

int QueueStatus::getFirstQueueCount() {
	return this->firstQueueElements;
}

int QueueStatus::getSecondQueueCount() {
	return this->secondQueueElements;
}

int QueueStatus::getThirdQueueCount() {
	return this->thirdQueueElements;
}