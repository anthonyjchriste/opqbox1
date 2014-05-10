#ifndef OPQPACKET_HPP
#define OPQPACKET_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

class OpqPacket
{
public:
    OpqPacket();
    OpqPacket(std::string encodedPacket);

    typedef struct __attribute__((__packed__)) {
        uint32_t magic;
        uint32_t type;
        uint32_t sequenceNumber;
        uint64_t deviceId;
        uint64_t timestamp;
        uint32_t bitfield;
        uint32_t payloadSize;
        uint32_t reserved[4];
        uint32_t checksum;
    } OpqPacketHeader;

    void debugInfo();
    std::string encodeOpqPacket();
    OpqPacketHeader header;
    void computeChecksum();
    std::vector<unsigned char> payload;
    void addPayload(uint8_t b);
    void addPayload(uint32_t i);
    void addPayload(uint64_t l);
    void addPayload(double d);
    void addPayload(std::string s);

private:
    OpqPacketHeader headerToByteOrder();
    void zeroReserved();
};

enum OpqPacketType {
    MEASUREMENT = 0,
    EVENT_FREQUENCY = 1,
    EVENT_VOLTAGE = 2,
    EVENT_DEVICE = 3,
    PING = 4,
    SETTING = 5,
    MONITOR = 6
};

#endif // OPQPACKET_HPP

