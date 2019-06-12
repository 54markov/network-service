#pragma once

#include <string>
#include <vector>

typedef enum
{
    S_USER = 0,
    S_NICE,
    S_SYSTEM,
    S_IDLE,
    S_IOWAIT,
    S_IRQ,
    S_SOFTIRQ,
    S_STEAL,
    S_GUEST,
    S_GUEST_NICE,
    NUM_CPU_STATES // last one
} cpuStates_t;

class CpuData
{
    public:
        std::string name;
        double usage;
        size_t times[NUM_CPU_STATES];
};

class CpuMonitor
{
    public:
        CpuMonitor() = default;
        ~CpuMonitor() = default;

        std::vector<CpuData> getUsage();

    private:
        void readProc_(std::vector<CpuData>& cpuData);
        size_t calcIdleTime_(const CpuData& cpuData);
        size_t calcActiveTime_(const CpuData& cpuData);
        void calcDiff_(const std::vector<CpuData>& a, std::vector<CpuData>& b);
};
