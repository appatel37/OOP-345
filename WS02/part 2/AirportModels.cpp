#include "AirportModels.h"
#include <fstream>
#include <iomanip>
#include <sstream>

namespace sdds {

    bool Airport::isEmpty() const {
        return m_code.empty() && m_name.empty() && m_city.empty() && m_state.empty() &&
               m_country.empty() && m_latitude == 0.0 && m_longitude == 0.0;
    }

    void
    Airport::printFormatted(std::ostream &ostream, const char *string, const std::string &basicString, bool isDouble) {
        ostream << std::setfill('.') << std::setw(20) << std::right << string << " : "
                << std::setfill('.') << std::setw(30) << std::left;
        if (isDouble) {
            double temp{};
            std::istringstream iss(basicString);
            iss >> std::setprecision(4) >> temp;
            iss.clear();
            ostream << temp << std::setfill(' ') << std::setw(0);
        } else {
            ostream << basicString << std::setfill(' ') << std::setw(0);
        }
        ostream << std::endl;

    }

    void Airport::print() const {
        if (isEmpty()) {
            std::cout << "Empty Airport" << std::endl;
        } else {
            printFormatted(std::cout, "Airport Code", m_code);
            printFormatted(std::cout, "Airport Name", m_name);
            printFormatted(std::cout, "City", m_city);
            printFormatted(std::cout, "State", m_state);
            printFormatted(std::cout, "Country", m_country);
            printFormatted(std::cout, "Latitude", std::to_string(m_latitude), true);
            printFormatted(std::cout, "Longitude", std::to_string(m_longitude), true);
        }
    }

    AirportLog::AirportLog() : m_airports(nullptr), m_size(0), m_capacity(0) {}

    AirportLog::AirportLog(const AirportLog &other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_airports = new Airport[m_capacity];

        for (size_t i = 0; i < m_size; i++) {
            m_airports[i] = other.m_airports[i];
        }
    }

    AirportLog::AirportLog(AirportLog &&other) noexcept {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_airports = other.m_airports;

        other.m_size = 0;
        other.m_capacity = 0;
        other.m_airports = nullptr;
    }

    AirportLog &AirportLog::operator=(const AirportLog &other) {
        if (this != &other) {
            delete[] m_airports;

            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_airports = new Airport[m_capacity];

            for (size_t i = 0; i < m_size; i++) {
                m_airports[i] = other.m_airports[i];
            }
        }
        return *this;
    }

    AirportLog &AirportLog::operator=(AirportLog &&other) noexcept {
        if (this != &other) {
            delete[] m_airports;

            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_airports = other.m_airports;

            other.m_size = 0;
            other.m_capacity = 0;
            other.m_airports = nullptr;
        }
        return *this;
    }

    AirportLog::AirportLog(const char *filename) : AirportLog() {
        std::ifstream file(filename);
        if (!file) {
            return;
        }

        std::string line;
        std::getline(file, line); 
        while (std::getline(file, line)) {
            m_size++;
        }

        m_capacity = m_size;
        m_airports = new Airport[m_capacity];

        file.clear();
        file.seekg(0, std::ios::beg);

        size_t index = 0;

        std::getline(file, line);

        while (std::getline(file, line)) {
            if (line.find("Airport Code") != std::string::npos) {
                continue; 
            }

            Airport airport;

            airport.m_code = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            airport.m_name = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            airport.m_city = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            airport.m_state = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            airport.m_country = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            airport.m_latitude = std::stod(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
            airport.m_longitude = std::stod(line.substr(0, line.find(',')));

            m_airports[index++] = airport;
        }
    }

    AirportLog::~AirportLog() {
        delete[] m_airports;
    }

    void AirportLog::addAirport(const Airport &a) {
        if (m_size >= m_capacity) {
            size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            Airport *newArray = new Airport[newCapacity];

            for (size_t i = 0; i < m_size; i++) {
                newArray[i] = m_airports[i];
            }

            delete[] m_airports;
            m_airports = newArray;
            m_capacity = newCapacity;
        }

        m_airports[m_size++] = a;
    }


    AirportLog AirportLog::findAirport(const char *state, const char *country) const {
        AirportLog result;

        for (size_t i = 0; i < m_size; i++) {
            if (m_airports[i].m_state == state && m_airports[i].m_country == country) {
                result.addAirport(m_airports[i]);
            }
        }

        return result;
    }

    const Airport &AirportLog::operator[](size_t index) const {
        if (index < m_size) {
            return m_airports[index];
        }
        static Airport empty;
        return empty;
    }

    AirportLog::operator size_t() const {
        return m_size;
    }

    std::ostream &operator<<(std::ostream &os, const Airport &a) {
        if (a.isEmpty()) {
            os << "Empty Airport";
        } else {
            a.print();
        }
        return os;
    }

}
