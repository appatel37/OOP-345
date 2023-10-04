#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds {

    class Timer {

    public:
        void start();
        long long stop();

    private:
        std::chrono::steady_clock::time_point start_time;

    };

}

#endif //SDDS_TIMER_H
