#include <misc_elistair/Driver.hpp>

using namespace misc_elistair;

static uint8_t computeCRC(uint8_t const* buffer, uint8_t length);

Driver::Driver()
    : iodrivers_base::Driver(INTERNAL_BUFFER_SIZE) {
}

int Driver::extractPacket(uint8_t const* buffer, size_t size) const {
    if (buffer[0] != 0xAA) {
        return -1;
    }
    else if (size > 2 && buffer[1] != 9) {
        return -1;
    }
    else if (size < 11) {
        return 0;
    }

    uint8_t actualCRC = computeCRC(buffer + 1, 9);
    if (actualCRC != buffer[10]) {
        return -1;
    }

    return 11;
}

void Driver::sendCommand(PowerMode powerMode, TorqueMode torqueMode, uint8_t torque) {
    if (torque > 10) {
        throw std::invalid_argument("invalid torque value, must be in [0, 10]");
    }

    uint8_t buffer[6];
    buffer[0] = 0xAA;
    buffer[1] = powerMode;
    buffer[2] = torqueMode == TORQUE_BUTTON ? 0xff : torque;
    buffer[3] = computeCRC(buffer + 1, 2);
    buffer[4] = '\r';
    buffer[5] = '\n';
    writePacket(buffer, 6);
}

Status Driver::read() {
    uint8_t buffer[INTERNAL_BUFFER_SIZE];
    readPacket(buffer, INTERNAL_BUFFER_SIZE);

    uint16_t lsbPower = buffer[2];
    uint16_t msbPower = buffer[3];
    uint16_t lsbCableLength = buffer[4];
    uint16_t msbCableLength = buffer[5];
    uint8_t cableSpeed = buffer[6];
    int8_t temperature = reinterpret_cast<int8_t&>(buffer[7]);
    uint16_t flightTimeHours = buffer[8];
    uint16_t flightTimeMinutes = buffer[9];

    Status status;
    status.time = base::Time::now();
    status.power = lsbPower + (msbPower << 8);
    status.cable_length = static_cast<float>(lsbCableLength + (msbCableLength << 8)) * 0.1;
    status.cable_speed = static_cast<float>(cableSpeed) * 0.1;
    status.temperature = temperature;
    status.flight_time = base::Time::fromSeconds(
        flightTimeHours * 3600 + flightTimeMinutes * 60
    );
    return status;
}

static const int BLFP_CRC_POLYNOME_4 = 0xD5;
static const int BLFP_CRC_INIT_VAL = 0x00;

static uint8_t computeCRC(uint8_t const* buffer, uint8_t length) {
    unsigned char crc = BLFP_CRC_INIT_VAL;
    unsigned char index = 0;
    uint8_t const* currentBytePtr = buffer;
    unsigned char remainingLength = length;

    while(remainingLength!= 0)
    {
        crc = crc ^ (*currentBytePtr);
        /* for each bit*/
        for(index = 0; index < 8; index++) {
            if( (crc & 0x80) != 0 )/* if the most significant bit is equal to 1*/
            {
                crc = (crc << 1) ^ BLFP_CRC_POLYNOME_4;
            }
            else
            {
                crc = (crc << 1);
            }
        }
        remainingLength--;
        currentBytePtr++;
    }
    return crc;
}