#pragma once

template <typename T>
class Service : public T
{
    public:
        Service() = default;
        ~Service() = default;

        void run()
        {
            T::run();
        }
};
