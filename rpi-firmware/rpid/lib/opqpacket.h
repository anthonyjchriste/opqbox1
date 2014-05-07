#ifndef OPQPACKET_HPP
#define OPQPACKET_HPP

#include <cstdint>
#include <utility>

#define HEADER_SIZE 59

struct OpqPacketHeader {
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

typedef std::pair<OpqPacketHeader, vector<uint_8t> > OpqPacket;

uint32_t computeChecksum(OpqPacket opqPacket)
{
    uint32_t sum = 0;
    uint8_t * p = &opqPacket;

    for(int i = 0; i < sizeof(OpqHeaderPacket); i++) {
        sum += p[i];
    }

    return sum;
}

#endif // OPQPACKET_HPP

