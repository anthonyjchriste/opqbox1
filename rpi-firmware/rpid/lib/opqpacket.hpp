#ifndef OPQPACKET_HPP
#define OPQPACKET_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

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

typedef std::pair<OpqPacketHeader, std::vector<unsigned char> > OpqPacket;
uint32_t computeChecksum(OpqPacket opqPacket);
std::string base64Encode(uint8_t bytes[]);
std::string base64Decode(std::string encodes);
OpqPacket makeOpqPacket(std::string encoded);
std::string encodeOpqPacket(OpqPacket opqPacket);

#endif // OPQPACKET_HPP

