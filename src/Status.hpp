#ifndef MISC_ELISTAIR_STATUS_HPP
#define MISC_ELISTAIR_STATUS_HPP

#include <base/Time.hpp>

namespace misc_elistair {
    /** Status reported by the Elistair Safe-T
     */
    struct Status {
        base::Time time;

        float power;
        float cable_length;
        float cable_speed;
        float temperature;
        base::Time flight_time;
    };
}

#endif