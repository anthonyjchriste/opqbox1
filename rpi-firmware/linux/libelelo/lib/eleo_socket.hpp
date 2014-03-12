#ifndef OPQ_ELEO_SOCKET
#define OPQ_ELEO_SOCKET
#include <string>
#include <vector>
#include <stdint.h>

namespace opq
{
namespace eleo
{

typedef struct PacketHeaderStruct
{
    uint32_t magic;
    uint32_t type;
    uint32_t sequence;
    uint64_t deviceId;
    uint64_t timeStamp;
    uint32_t bitfield;
    uint32_t size;
    uint64_t reserved[2];
    uint32_t checksum;
} PacketHeader;

static const std::string UPGRADE_HEADER ="GET [PATH] HTTP/1.1\r\n"
        "Host: [HOST]\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
        "Sec-WebSocket-Version: 13\r\n"
        "\r\n";

class Socket
{
public:
    Socket(std::string);
    ~Socket();
    void send(const unsigned char*, int);
    void send(const std::vector<unsigned char> );
    Socket& operator << (const std::vector<unsigned char> );
    Socket& operator << (const std::string );
private:
    std::string _url;
    int _sock;
    std::string _host;
    std::string _path;
    int _port;
};
}
}


#endif /* OPQ_ELEO_SOCKET */
