#include <cpu-monitor/cpu-monitor.hpp>
#include <exception/exception.hpp>

#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>

std::vector<CpuData> CpuMonitor::getUsage()
{
    std::vector<CpuData> prev;
    std::vector<CpuData> curr;

    CpuMonitor::readProc_(prev);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    CpuMonitor::readProc_(curr);

    CpuMonitor::calcDiff_(prev, curr);

    return curr;
}

void CpuMonitor::readProc_(std::vector<CpuData>& cpuData)
{
    std::ifstream file("/proc/stat");
    if (!file.is_open())
        throw Exception("Can't open: /proc/stat" +
                        std::string(::strerror(errno)), errno);

    std::string line;

    const std::string cpu("cpu");

    while (std::getline(file, line))
    {
        if (!line.compare(0, cpu.size(), cpu))
        {
            std::istringstream is(line);

            auto cpu = CpuData();

            is >> cpu.name;
            for (auto i = 0; i < NUM_CPU_STATES; ++i)
                is >> cpu.times[i];

            cpuData.push_back(cpu);
        }
    }

    file.close();
}

size_t CpuMonitor::calcIdleTime_(const CpuData& cpuData)
{
    return cpuData.times[S_IDLE] + cpuData.times[S_IOWAIT];
}

size_t CpuMonitor::calcActiveTime_(const CpuData& cpuData)
{
    return cpuData.times[S_USER]    + cpuData.times[S_NICE]  +
           cpuData.times[S_SYSTEM]  + cpuData.times[S_IRQ]   +
           cpuData.times[S_SOFTIRQ] + cpuData.times[S_STEAL] +
           cpuData.times[S_GUEST]   + cpuData.times[S_GUEST_NICE];
}

void CpuMonitor::calcDiff_(const std::vector<CpuData>& a, std::vector<CpuData>& b)
{
    if (a.size() != b.size())
        throw Exception("Cpu vectors are not equal", -1);

    for (size_t i = 0; i < a.size(); ++i)
    {
        auto active = calcActiveTime_(b[i]) - calcActiveTime_(a[i]);
        auto idle   = calcIdleTime_(b[i]) - calcIdleTime_(a[i]);
        b[i].usage = (100.f * active / (active + idle));
    }
}
