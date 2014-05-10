#include "opqpacket.hpp"
#include <cstring>
#include <vector>
#include <cstdint>
#include <iostream>
#include "base64.hpp"


#include <string>

uint32_t computeChecksum(OpqPacket opqPacket)
{
    uint32_t sum = 0;
    uint8_t * p = (unsigned char *) &opqPacket.first;

    for(int i = 0; i < sizeof(OpqPacketHeader); i++) {
        sum += p[i];
    }

    for(int i = 0; i < opqPacket.second.size(); i++) {
        sum += opqPacket.second[i];
    }

    return sum;
}

std::string base64Encode(uint8_t bytes[], int length)
{
    std::string out = base64::base64_encode(bytes,length);
    return out;
}

std::string base64Decode(std::string encoded)
{
    std::string out;


    return out;
}

OpqPacket decodeOpqPacketet(std::string encoded)
{
    struct OpqPacketHeader opqPacketHeader;
    std::vector<uint8_t> payload;
    std::string decoded = base64Decode(encoded);
    const char *p = decoded.c_str();
    std::memmove(&opqPacketHeader, p, sizeof(OpqPacketHeader));

    p += sizeof(OpqPacketHeader);
    for(int i = sizeof(OpqPacketHeader); i < decoded.size(); i++) {
        payload.push_back(*p);
        p++;
    }

    return std::make_pair(opqPacketHeader, payload);
}

std::string encodeOpqPacket(OpqPacket opqPacket)
{
    int length = sizeof(OpqPacketHeader) + opqPacket.second.size();
    uint8_t data[length];
    std::memmove(data, &opqPacket.first, sizeof(OpqPacketHeader));
    std::memcpy(data + sizeof(OpqPacketHeader), opqPacket.second.data(), opqPacket.second.size());


    std::string encoded = base64Encode(data, length);
    return encoded;
}

void printHeader(OpqPacketHeader header)
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
