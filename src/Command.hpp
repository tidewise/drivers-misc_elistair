#ifndef MISC_ELISTAIR_COMMAND_HPP
#define MISC_ELISTAIR_COMMAND_HPP

#include <cstdint>

namespace misc_elistair {
    /** Controls the power through the tether */
    enum PowerMode {
        POWER_OFF = 0, //! Power off
        POWER_ON = 1, //! Power on
        POWER_BUTTON = 0xff //! Power controlled by physical button
    };

    /** Controls how the torque is controlled */
    enum TorqueMode {
        TORQUE_SOFTWARE = 0, //! torque controlled by software
        TORQUE_BUTTON = 1 //! torque controlled by physical button
    };

    /** Command as sent to the Elistair Safe-T
     */
    struct Command {
        PowerMode power_mode;
        TorqueMode torque_mode;

        /** Torque setpoint in 1/10th of max
         *
         * I.e. 2 is 20% of max torque. Only used
         * if torque_mode is TORQUE_SOFTWARE
         */
        uint8_t torque;
    };
}

#endif