#include <iostream>
#include <fstream>
#include <string>
#include "scheduler.hpp"
#include "policy.hpp"

int main(void) {

    std::ifstream inputfile("input.txt");
    std::vector<int> arrivalTimes;
    std::vector<int> burstTimes;
    /*char line[256];*/
    int index = 0;
    std::string token;
    if (inputfile.is_open()) {
        while (inputfile >> token) {
            std::cout << token << std::endl;
            int value = std::stoi(token);
            
            if (index == 0) {
                std::cout << "Pushing into arrivalTimes: " << value << std::endl;
                arrivalTimes.push_back(value);
            }
            else {
                std::cout << "Pushing into burstTimes: " << value << std::endl;
                burstTimes.push_back(value);
            }
            index = (index + 1) % 2;
        }

        inputfile.close();
    }
    else {
        std::cout << "Error reading from file" << std::endl;
        return 1;
    }
    
    std::cout << "arrivalTimes.size: " << arrivalTimes.size() << std::endl;
    std::string thing;
    std::cin >> thing;
    //return 0;

    std::vector<Process> processList;

    for (int i = 0; i < arrivalTimes.size(); i++) {
        processList.push_back(Process(arrivalTimes.at(i), burstTimes.at(i)));
    }

    std::cout << "Process list: " << std::endl;
    for (std::vector<Process>::iterator it = processList.begin(); it != processList.end(); it++) {
        std::cout << "dodo" << std::endl;
    }

    // replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {0,2,3,8,19,33,34};
    std::vector<int> burst_times {8,21,133,39,67,114,54};

    //PaperPolicy selectedPolicy(processList);
    Policy* selectedPolicy = new PaperPolicy(processList);

    //Scheduler scheduler(arrival_times, burst_times);
    Scheduler scheduler(processList, selectedPolicy);
    scheduler.runSchedulerNew();
    scheduler.printBenchMarks(); 

    std::cout << "Press any key to exit..." << std::endl;
    std::string input;
    std::cin >> input;
    return 0;
}