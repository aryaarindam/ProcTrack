#include "../include/cpu.hpp"
#include <mach/mach.h>

#include "../include/memory.hpp"
#include <iostream>
#include <mach/mach.h>
#include <sys/types.h>
#include <sys/sysctl.h>


float getCPUUsage() {
    host_cpu_load_info_data_t cpuinfo;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    kern_return_t kr = host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO,
                                       (host_info_t)&cpuinfo, &count);

    if (kr != KERN_SUCCESS) return -1;

    static uint64_t prevUser = 0, prevSystem = 0, prevIdle = 0, prevNice = 0;

    uint64_t user = cpuinfo.cpu_ticks[CPU_STATE_USER];
    uint64_t system = cpuinfo.cpu_ticks[CPU_STATE_SYSTEM];
    uint64_t idle = cpuinfo.cpu_ticks[CPU_STATE_IDLE];
    uint64_t nice = cpuinfo.cpu_ticks[CPU_STATE_NICE];

    uint64_t totalTicks = (user - prevUser) + (system - prevSystem) +
                          (idle - prevIdle) + (nice - prevNice);

    uint64_t totalActive = (user - prevUser) + (system - prevSystem) + (nice - prevNice);

    prevUser = user;
    prevSystem = system;
    prevIdle = idle;
    prevNice = nice;

    if (totalTicks == 0) return 0;

    return (100.0f * totalActive) / totalTicks;
}
