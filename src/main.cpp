#include <ncurses.h>
#include <thread>
#include <chrono>
#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include "../include/process.hpp"

int main() {
    initscr();              // Start ncurses mode
    noecho();               // Don't echo keypresses
    curs_set(FALSE);        // Hide cursor
    nodelay(stdscr, TRUE);  // Don't block on getch()

    while (true) {
        clear();

        float cpu = getCPUUsage();
        float mem = getMemoryUsagePercent();

        mvprintw(1, 2, "ProcTrack Monitor");
        mvprintw(3, 2, "CPU Usage: %.2f %%", cpu);
        mvprintw(4, 2, "Memory Usage: %.2f %%", mem);

        mvprintw(6, 2, "Running Processes:");
        mvprintw(7, 2, "------------------");

        FILE* pipe = popen("ps -axo pid,comm | head -n 15", "r");
        if (pipe) {
            char buffer[256];
            int row = 8;
            bool skipHeader = true;

            while (fgets(buffer, sizeof(buffer), pipe)) {
                if (skipHeader) {
                    skipHeader = false;
                    continue;
                }
                mvprintw(row++, 2, "%s", buffer);
            }
            pclose(pipe);
        }

        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (getch() == 'q') break;  // Press 'q' to exit
    }

    endwin();  // End ncurses mode
    return 0;
}
