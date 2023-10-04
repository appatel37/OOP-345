#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <string>

namespace sdds {

    struct Airport {
        std::string m_code{};
        std::string m_name{};
        std::string m_city{};
        std::string m_state{};
        std::string m_country{};
        double m_latitude{};
        double m_longitude{};
        bool isEmpty() const;
        void print() const;
        static void printFormatted(std::ostream &ostream, const char *label, const std::string &value, bool isDouble = false);
    };

    std::ostream &operator<<(std::ostream &os, const Airport &a);

    class AirportLog {
        Airport* m_airports;
        size_t m_size;
        size_t m_capacity;

    public:
        AirportLog();
        AirportLog(const char* filename);
        ~AirportLog();
        void addAirport(const Airport& a);
        AirportLog findAirport(const char* state, const char* country) const;
        const Airport& operator[](size_t index) const;
        operator size_t() const;
    };

}

#endif // SDDS_AIRPORTMODELS_H
