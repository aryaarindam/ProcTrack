#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include "../include/process.hpp"
#include <ncurses.h>

void printRunningProcessesNcurses(int startRow) {
    auto processes = getRunningProcesses();  // assuming this function exists

    int row = startRow;
    for (const auto& p : processes) {
        mvprintw(row++, 4, "%-7d %-10s %-20s", p.pid, p.user.c_str(), p.command.c_str());
        if (row > LINES - 2) break;
    }
}


std::vector<ProcessInfo> getRunningProcesses() {
    std::vector<ProcessInfo> processes;

    FILE* pipe = popen("ps -axo pid,user,args | head -n 15", "r");
    if (!pipe) return processes;

    char buffer[512];
    fgets(buffer, sizeof(buffer), pipe);  // Skip header

    while (fgets(buffer, sizeof(buffer), pipe)) {
        ProcessInfo p;
        std::string line(buffer);
        std::istringstream iss(line);

        if (!(iss >> p.pid >> p.user)) continue;

        // Safely extract command after user
        size_t cmd_pos = line.find(p.user) + p.user.length();
        if (cmd_pos != std::string::npos) {
            p.command = line.substr(cmd_pos);
            p.command.erase(0, p.command.find_first_not_of(" \t"));  // Trim leading spaces
        } else {
            p.command = "";
        }

        processes.push_back(p);
    }

    pclose(pipe);
    return processes;
}
