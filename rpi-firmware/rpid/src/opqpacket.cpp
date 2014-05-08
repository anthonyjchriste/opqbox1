#include "opqpacket.hpp"

uint32_t computeChecksum(OpqPacket opqPacket)
{
    uint32_t sum = 0;
    uint8_t * p = &opqPacket.first;

    for(int i = 0; i < sizeof(OpqHeaderPacketHeader); i++) {
        sum += p[i];
    }

    for(int i = 0; i < opqPacket.second.size(); i++) {
        sum += opqPacket.second[i];
    }

    return sum;
}
