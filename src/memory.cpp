#include "../include/memory.hpp"
#include <iostream>
#include <mach/mach.h>
#include <sys/types.h>
#include <sys/sysctl.h>

float getMemoryUsagePercent() {
    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    vm_statistics_data_t vm_stat;
    kern_return_t kr = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vm_stat, &count);

    if (kr != KERN_SUCCESS) return -1;

    int64_t pageSize;
    size_t size = sizeof(pageSize);
    sysctlbyname("hw.pagesize", &pageSize, &size, nullptr, 0);

    int64_t freeMemory = (int64_t)vm_stat.free_count * pageSize;
    int64_t activeMemory = (int64_t)vm_stat.active_count * pageSize;
    int64_t inactiveMemory = (int64_t)vm_stat.inactive_count * pageSize;
    int64_t wiredMemory = (int64_t)vm_stat.wire_count * pageSize;

    int64_t usedMemory = activeMemory + inactiveMemory + wiredMemory;
    int64_t totalMemory = usedMemory + freeMemory;

    if (totalMemory == 0) return 0;

    return 100.0f * usedMemory / totalMemory;
}

void printMemoryStats() {
    float percent = getMemoryUsagePercent();
    std::cout << "Memory Usage: " << percent << "%" << std::endl;
}
