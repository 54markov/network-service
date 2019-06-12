#include <service/signal.hpp>
#include <exception/exception.hpp>

#include <iostream>

#include <csignal>

#include <string.h>

namespace
{
    static volatile std::sig_atomic_t exit_;
}

SignalHandler::SignalHandler()
{
    if (std::signal(SIGINT, SignalHandler::process) == SIG_ERR)
        throw Exception("Can't set signal(): " +
                        std::string(::strerror(errno)), errno);
    exit_ = 0;
}

void SignalHandler::process(int signal)
{
    std::cerr << "Catched signal: " << ::strsignal(signal) << std::endl;
    exit_ = 1;
}

bool SignalHandler::isExit()
{
    return exit_;
}
