#include <ncurses.h>
#include <thread>
#include <chrono>
#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include "../include/process.hpp"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    while (true) {
        clear();

        float cpu = getCPUUsage();
        float mem = getMemoryUsagePercent();

        mvprintw(1, 2, "CPU Usage: %.2f%%", cpu);
        mvprintw(2, 2, "Memory Usage: %.2f%%", mem);

        printRunningProcessesNcurses(4);

        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    endwin();
    return 0;
}
