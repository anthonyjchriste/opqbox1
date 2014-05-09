#include "opqpacket.hpp"
#include "base64/encode.h"
#include "base64/decode.h"
#include <cstring>
#include <vector>
#include <cstdint>



#include <string>

namespace websocketpp {

static std::string const base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (c == 43 || // +
           (c >= 47 && c <= 57) || // /-9
           (c >= 65 && c <= 90) || // A-Z
           (c >= 97 && c <= 122)); // a-z
}

inline std::string base64_encode(unsigned char const * bytes_to_encode, unsigned
    int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                              ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                              ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++) {
                ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for(j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                          ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                          ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) {
            ret += base64_chars[char_array_4[j]];
        }

        while((i++ < 3)) {
            ret += '=';
        }
  }

  return ret;
}

inline std::string base64_encode(std::string const & data) {
    return base64_encode(reinterpret_cast<const unsigned char *>(data.data()),data.size());
}

inline std::string base64_decode(std::string const & encoded_string) {
    size_t in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++) {
                char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
            }

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++) {
                ret += char_array_3[i];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;

        for (j = 0; j <4; j++)
            char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) {
            ret += static_cast<std::string::value_type>(char_array_3[j]);
        }
    }

    return ret;
}

} // namespace websocketpp



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
    std::string out = websocketpp::base64_encode(bytes,length);
    for(size_t i = 0; i < out.length(); i++)
    {
        std::cout << out[i] << std::endl;
    }
    std::cout << out << std::endl;

    return out;
}

std::string base64Decode(std::string encoded)
{
    std::string out;
    base64::decoder decoder;
    decoder.decode(encoded.c_str(), (int) encoded.length(), (char *) out.c_str());

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

    std::cout << "length:" << length << std::endl;
    for(int i = 0; i < length; i++) {
        //std::cout << "data[" << std::dec << i << "] = \"" << std::hex << (int) data[i] << "\"\n";
    }

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
