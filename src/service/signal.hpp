#pragma once

class SignalHandler
{
    public:
        SignalHandler();
        ~SignalHandler() = default;

        static void process(int signal);
        bool isExit();
};
