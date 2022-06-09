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
            if (index == 0) {
                processNames.push_back(token);
            }
            else {
                int value = std::stoi(token);

                if (index == 1) {
                    arrivalTimes.push_back(value);
                }
                else {
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

    std::vector<Process> processList;

    for (int i = 0; i < arrivalTimes.size(); i++) {
        processList.push_back(Process(processNames.at(i), arrivalTimes.at(i), burstTimes.at(i)));
    }

    std::cout << "Process list: " << std::endl;
    for (std::vector<Process>::iterator it = processList.begin(); it != processList.end(); it++) {
        Process p = *it;
        std::cout << p.getName() << " " << p.getArrivalTime() << " " << p.getTotalBurstTime() << std::endl;
    }

    int policyToUse = 1; //change to 0 to use the original paper implementation, 1 for the baseline implementation, 2 for custom implementation
    Policy* selectedPolicy;

    switch (policyToUse) {
    case 0:
        selectedPolicy = new PaperPolicy(processList);
        break;
    case 1:
        selectedPolicy = new BasePolicy(processList);
        break;
    case 2:
        selectedPolicy = new OurPolicy(processList);
        break;
    default:
        std::cout << "Error determing policy to use" << std::endl;
        return 1;
    }

    Scheduler scheduler(processList, selectedPolicy);
    scheduler.runScheduler();
    scheduler.printBenchMarks(); 

    std::cout << "Press any key to exit..." << std::endl;
    std::string input;
    std::cin >> input;
    return 0;
}