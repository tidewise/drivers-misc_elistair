#ifndef MISC_ELISTAIR_DRIVER_HPP
#define MISC_ELISTAIR_DRIVER_HPP

#include <iodrivers_base/Driver.hpp>
#include <misc_elistair/Command.hpp>
#include <misc_elistair/Status.hpp>

namespace misc_elistair {
    /** Driver for Elistair Safe-T RS232 protocol
     *
     * Usually published over UDP
     */
    class Driver : public iodrivers_base::Driver {
    public:
        static const int MAX_MESSAGE_SIZE = 1024;
        static const int INTERNAL_BUFFER_SIZE = MAX_MESSAGE_SIZE * 10;

    private:
        int extractPacket(uint8_t const* buffer, size_t size) const;

    public:
        Driver();

        void sendCommand(PowerMode powerMode, TorqueMode torqueMode, uint8_t torque);
        Status read();
    };
}

#endif