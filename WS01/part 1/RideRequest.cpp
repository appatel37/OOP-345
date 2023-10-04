#include <iomanip>
#include "RideRequest.h"

namespace sdds {
    double g_taxrate = 0.0;
    double g_discount = 0.0;

    RideRequest::RideRequest() : m_price(0.0), m_discount(false) {
        m_customerName[0] = '\0';
        m_rideDescription[0] = '\0';
    }

    void RideRequest::read(std::istream& is) {
        is.getline(m_customerName, 11, ',');
        is.getline(m_rideDescription, 26, ',');
        is >> m_price;
        is.ignore(1000, ',');
        char discountStatus;
        is >> discountStatus;
        m_discount = (discountStatus == 'Y');
        is.ignore(1000, '\n');
    }

    void RideRequest::display() const {
        static int counter = 0;
        counter++;

        std::cout << std::left << std::setw(2) << counter << ". ";
        if (m_customerName[0] == '\0') {
            std::cout << "No Ride Request\n";
        } else {
            double priceWithTax = m_price * (1.0 + g_taxrate);
            std::cout << std::setw(10) << m_customerName << "|" << std::setw(25) << m_rideDescription;
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
