#include <iostream>
#include <fstream>
#include <string>
#include "scheduler.hpp"
#include "policy.hpp"

int main(void) {

    std::ifstream inputfile("input.txt");
    std::vector<std::string> processNames;
    std::vector<int> arrivalTimes;
    std::vector<int> burstTimes;
    int index = 0;
    std::string token;
    if (inputfile.is_open()) {
        while (inputfile >> token) {
            std::cout << token << std::endl;
            if (index == 0) {
                std::cout << "Pushing into processNames: " << token << std::endl;
                processNames.push_back(token);
            }
            else {
                int value = std::stoi(token);

                if (index == 1) {
                    std::cout << "Pushing into arrivalTimes: " << value << std::endl;
                    arrivalTimes.push_back(value);
                }
                else {
                    std::cout << "Pushing into burstTimes: " << value << std::endl;
                    burstTimes.push_back(value);
                }
            }
            
            index = (index + 1) % 3;
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
        processList.push_back(Process(processNames.at(i), arrivalTimes.at(i), burstTimes.at(i)));
    }

    std::cout << "Process list: " << std::endl;
    for (std::vector<Process>::iterator it = processList.begin(); it != processList.end(); it++) {
        Process p = *it;
        std::cout << p.getName() << " " << p.getArrivalTime() << " " << p.getTotalBurstTime() << std::endl;
    }

    // replace with reading a file and importing to these vectors
    std::vector<int> arrival_times {0,2,3,8,19,33,34};
    std::vector<int> burst_times {8,21,133,39,67,114,54};

    //PaperPolicy selectedPolicy(processList);
    //Policy* selectedPolicy = new PaperPolicy(processList);
    Policy* selectedPolicy = new BasePolicy(processList);

    //Scheduler scheduler(arrival_times, burst_times);
    Scheduler scheduler(processList, selectedPolicy);
    scheduler.runSchedulerNew();
    scheduler.printBenchMarks(); 

    std::cout << "Press any key to exit..." << std::endl;
    std::string input;
    std::cin >> input;
    return 0;
}