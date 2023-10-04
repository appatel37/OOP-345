#include "Timer.h"

namespace sdds {

    void Timer::start() {
        start_time = std::chrono::steady_clock::now();
    }

    long long Timer::stop() {
        auto end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        return duration.count();
    }


} 
