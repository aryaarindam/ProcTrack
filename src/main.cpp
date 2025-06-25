#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include "../include/process.hpp"

int main() {
    initscr();              
    noecho();              
    curs_set(FALSE);        
    start_color();          

    init_pair(1, COLOR_GREEN, COLOR_BLACK);   // CPU
    init_pair(2, COLOR_CYAN, COLOR_BLACK);    // Memory
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // Process Header
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // Project Title

    while (true) {
        clear();

        // Custom Project Title
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(0, 2, "ProcTrack - System Monitor (by Arindam Arya)");
        attroff(COLOR_PAIR(4) | A_BOLD);

        // CPU Usage
        attron(COLOR_PAIR(1));
        mvprintw(2, 2, "CPU Usage: %.2f%%", getCPUUsage());
        attroff(COLOR_PAIR(1));

        // Memory Usage
        attron(COLOR_PAIR(2));
        mvprintw(3, 2, "Memory Usage: %.2f%%", getMemoryUsagePercent());
        attroff(COLOR_PAIR(2));

        // Process Table Header
        attron(COLOR_PAIR(3));
        mvprintw(5, 4, "PID     USER       COMMAND");
        attroff(COLOR_PAIR(3));

        // Process List
        printRunningProcessesNcurses(6);  

        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    endwin(); 
    return 0;
}
