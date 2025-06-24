#include "../include/process.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

void printRunningProcesses() {
    std::cout << "\nRunning Processes:\n";
    std::cout << "------------------\n";

    FILE* pipe = popen("ps -axo pid,comm", "r");
    if (!pipe) {
        std::cerr << "Failed to fetch processes\n";
        return;
    }

    char buffer[256];
    bool skipHeader = true;
    while (fgets(buffer, sizeof(buffer), pipe)) {
        if (skipHeader) {
            skipHeader = false;
            continue; 
        }

        std::string line(buffer);
        std::istringstream iss(line);
        std::string pid, command;

        iss >> pid;
        getline(iss, command);

        std::cout << "PID: " << pid << " | Command: " << command << std::endl;
    }

    pclose(pipe);
}
