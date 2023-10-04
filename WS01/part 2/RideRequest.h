#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>

namespace sdds {
    extern double g_taxrate;
    extern double g_discount;

    class RideRequest {
        char m_customerName[11];
        char* m_rideDescription;
        double m_price;
        bool m_discount;

    public:
        RideRequest();
        ~RideRequest();
        RideRequest(const RideRequest& other);
        RideRequest& operator=(const RideRequest& other);
        void read(std::istream& is);
        bool isEmpty() const;
        void display() const;
    };

    void list_arguments(int argc, char* argv[], bool with_title = false);
}

#endif // SDDS_RIDEREQUEST_H
