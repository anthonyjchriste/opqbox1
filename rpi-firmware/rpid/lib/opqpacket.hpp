#ifndef OPQPACKET_HPP
#define OPQPACKET_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct __attribute__((__packed__)) OpqPacketHeader {
    uint32_t magic;
    uint32_t type;
    uint32_t sequenceNumber;
    uint64_t deviceId;
    uint64_t timestamp;
    uint32_t bitfield;
    uint32_t payloadSize;
    uint32_t reserved[4];
    uint32_t checksum;
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

typedef std::pair<OpqPacketHeader, std::vector<unsigned char> > OpqPacket;
std::string base64Encode(uint8_t bytes[], int length);
std::string base64Decode(std::string encodes);
OpqPacket makeOpqPacket(std::string encoded);
std::string encodeOpqPacket(OpqPacket opqPacket);
uint32_t computeChecksum(OpqPacket opqPacket);

void printHeader(OpqPacketHeader header);

#endif // OPQPACKET_HPP

