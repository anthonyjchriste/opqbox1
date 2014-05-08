#include "opqpacket.hpp"
#include "base64/encode.h"
#include "base64/decode.h"
#include <cstring>
#include <vector>
#include <cstdint>

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

std::string base64Encode(uint8_t bytes[])
{
    std::string plainText;
    base64::encoder encoder;
    encoder.encode((const char *) bytes, (int) sizeof(bytes), (char *) plainText.c_str());
    return plainText;
}

std::string base64Decode(std::string encoded)
{
    std::string out;
    base64::decoder decoder;
    decoder.decode(encoded.c_str(), (int) encoded.length(), (char *) out.c_str());

    return out;
}

OpqPacket makeOpqPacket(std::string encoded)
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
