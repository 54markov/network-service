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

void CpuMonitor::readProc_(std::vector<CpuData>& v)
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

            auto cpuData = CpuData();

            // Reads cpu label
            is >> cpuData.name;

            // Reads times
            for (auto i = 0; i < NUM_CPU_STATES; ++i)
                is >> cpuData.times[i];

            v.push_back(cpuData);
        }
    }

    file.close();
}

size_t CpuMonitor::calcIdleTime_(const CpuData& c)
{
    return c.times[S_IDLE] + c.times[S_IOWAIT];
}

size_t CpuMonitor::calcActiveTime_(const CpuData& c)
{
    return c.times[S_USER]  + c.times[S_NICE]    + c.times[S_SYSTEM] +
           c.times[S_IRQ]   + c.times[S_SOFTIRQ] + c.times[S_STEAL]  +
           c.times[S_GUEST] + c.times[S_GUEST_NICE];
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
