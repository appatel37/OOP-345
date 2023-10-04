#include <iomanip>
#include <cstring>
#include "RideRequest.h"

namespace sdds {
    double g_taxrate = 0.0;
    double g_discount = 0.0;

    RideRequest::RideRequest() {
        m_customerName[0] = '\0';
        m_rideDescription = nullptr;
        m_price = 0.0;
        m_discount = false;
    }

    RideRequest::~RideRequest() {
        delete[] m_rideDescription;
    }

    RideRequest::RideRequest(const RideRequest& other) : m_rideDescription(nullptr) {
        *this = other;
    }

    RideRequest& RideRequest::operator=(const RideRequest& other) {
        if (this != &other) {
            std::strncpy(m_customerName, other.m_customerName, 10);
            m_customerName[10] = '\0';

            delete[] m_rideDescription;
            if (other.m_rideDescription) {
                m_rideDescription = new char[std::strlen(other.m_rideDescription) + 1];
                std::strcpy(m_rideDescription, other.m_rideDescription);
            }
            else {
                m_rideDescription = nullptr;
            }

            m_price = other.m_price;
            m_discount = other.m_discount;
        }
        return *this;
    }

    void RideRequest::read(std::istream& is) {
        is.getline(m_customerName, 11, ',');
        delete[] m_rideDescription;
        m_rideDescription = nullptr;
        char buffer[256];
        is.getline(buffer, 256, ',');
        m_rideDescription = new char[std::strlen(buffer) + 1];
        std::strcpy(m_rideDescription, buffer);
        is >> m_price;
        is.ignore(1000, ',');
        char discountStatus;
        is >> discountStatus;
        m_discount = (discountStatus == 'Y');
        is.ignore(1000, '\n');
    }

    bool RideRequest::isEmpty() const {
        return m_customerName[0] == '\0';
    }

    void RideRequest::display() const {
        static int counter = 0;
        counter++;

        std::cout << std::left << std::setw(2) << counter << ". ";
        if (isEmpty()) {
            std::cout << "No Ride Request\n";
        } else {
            double priceWithTax = m_price * (1.0 + g_taxrate);
            std::cout << std::setw(10) << m_customerName << "|";
            std::cout << std::setw(strlen(m_rideDescription) > 26 ? strlen(m_rideDescription) - 1 : 25)
                      << m_rideDescription;
            std::cout << "|" << std::setw(12) << std::fixed << std::setprecision(2) << priceWithTax;
            std::cout << "|";
            if (m_discount) {
                double priceWithDiscount = priceWithTax - g_discount;
                std::cout << std::setw(13) << std::right << std::fixed << std::setprecision(2) <<  priceWithDiscount;
            }
            std::cout << std::endl;
        }
    }

    void list_arguments(int argc, char **argv, bool with_title) {
        if (with_title) {
            std::cout << "Command Line:\n";
            std::cout << "--------------------------\n";
        }
        for (int i = 0; i < argc; i++)
            std::cout << "  " << i + 1 << ": " << argv[i] << "\n";
        if (with_title)
            std::cout << "--------------------------\n\n";
    }
}
