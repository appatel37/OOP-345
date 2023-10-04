#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>

namespace sdds {
    extern double g_taxrate;
    extern double g_discount;

    class RideRequest {
        char m_customerName[11];
        char m_rideDescription[26];
        double m_price;
        bool m_discount;

    public:
        RideRequest();
        void read(std::istream& is);
        void display() const;
    };

    void list_arguments(int argc, char* argv[], bool with_title = false);
}

#endif // SDDS_RIDEREQUEST_H
