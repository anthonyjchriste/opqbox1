#include "base64.hpp"
#include "opqpacket.hpp"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <endian.h>
#include <string>
#include <vector>

OpqPacket::OpqPacket()
{
    zeroReserved();
    header.checksum = 0;
    header.payloadSize = 0;
}

OpqPacket::OpqPacket(std::string encodedPacket)
{
    std::string decoded = base64::base64_decode(encodedPacket);
    const char *p = decoded.c_str();
    std::memmove(&header, p, sizeof(OpqPacketHeader));

    p += sizeof(OpqPacketHeader);
    for(int i = sizeof(OpqPacketHeader); i < decoded.size(); i++) {
        payload.push_back(*p);
        p++;
    }

}

void OpqPacket::zeroReserved()
{
    for(int i = 0; i < 4; i++) header.reserved[i] = 0;
}

void OpqPacket::computeChecksum()
{
    uint32_t sum = 0;
    uint8_t * p = (unsigned char *) &header;

    for(int i = 0; i < sizeof(OpqPacketHeader); i++) {
        sum += p[i];
    }

    for(int i = 0; i < payload.size(); i++) {
        sum += payload[i];
    }
    header.checksum = sum;
}

void OpqPacket::addPayload(uint8_t b)
{
    payload.push_back(b);
    header.payloadSize++;
}

void OpqPacket::addPayload(uint32_t i)
{
    uint32_t converted = htobe32(i);
    uint8_t * p = (uint8_t *) &converted;

    for(int j = 0; j < sizeof(converted); j++) {
        payload.push_back(p[j]);
        header.payloadSize++;
    }
}

void OpqPacket::addPayload(uint64_t l) {
    uint64_t converted = htobe64(l);
    uint8_t * p = (uint8_t *) &converted;

    for(int j = 0; j < sizeof(converted); j++) {
        payload.push_back(p[j]);
        header.payloadSize++;
    }
}

void OpqPacket::addPayload(double d)
{
    uint32_t * p = (uint32_t *) &d;
    addPayload((uint32_t) p[1]);
    addPayload((uint32_t) p[0]);
}

void OpqPacket::addPayload(std::string s)
{
    uint8_t * p = (uint8_t *) s.c_str();
    for(int i = 0; i < s.length(); i++)
    {
        payload.push_back(p[i]);
        header.payloadSize++;
    }
}


std::string OpqPacket::encodeOpqPacket()
{
    int length = sizeof(OpqPacketHeader) + payload.size();
    uint8_t data[length];
    OpqPacketHeader networkHeader = headerToByteOrder();
    std::memmove(data, &networkHeader, sizeof(OpqPacketHeader));
    std::memcpy(data + sizeof(OpqPacketHeader), payload.data(), payload.size());
    std::string encoded = base64::base64_encode(data, length);
    return encoded;
}

OpqPacket::OpqPacketHeader OpqPacket::headerToByteOrder()
{
    OpqPacketHeader converted = header;
    converted.magic = htobe64(header.magic);
    converted.type = htobe32(header.type);
    converted.sequenceNumber = htobe32(header.sequenceNumber);
    converted.deviceId = htobe64(header.deviceId);
    converted.timestamp = htobe64(header.timestamp);
    converted.bitfield = htobe32(header.bitfield);
    converted.payloadSize = htobe32(header.payloadSize);
    converted.checksum = htobe32(header.checksum);
    return converted;
}


void OpqPacket::debugInfo()
{
    std::cout << "magic: " << header.magic << "\n";
    std::cout << "type: " << header.type << "\n";
    std::cout << "seq #: " << header.sequenceNumber << "\n";
    std::cout << "device id: " << header.deviceId << "\n";
    std::cout << "timestamp: " << header.timestamp << "\n";
    std::cout << "bitfield: " << header.bitfield << "\n";
    std::cout << "payload size: " << header.payloadSize << "\n";
    std::cout << "checksum: " << header.checksum << "\n";
}


