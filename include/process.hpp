#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>
#include <string>

struct ProcessInfo {
    int pid;
    std::string user;
    std::string command;
};

std::vector<ProcessInfo> getRunningProcesses();
void printRunningProcessesNcurses(int startRow);

#endif
