#ifndef OPQWEBSOCKET_HPP
#define OPQWEBSOCKET_HPP

#include "datastructures.hpp"
#include "easywsclient.hpp"
#include "opqpacket.hpp"

#include <cstdint>
#include <string>
#include <queue>

class OpqWebsocket
{
public:
    OpqWebsocket();
    void listen();
    void consumeQueue();
    void send(std::string message);
    void send(OpqPacket packet);
    std::queue<OpqFrame> frames;

    ~OpqWebsocket()
    {
        if(ws_ != NULL && ws_->getReadyState() != easywsclient::WebSocket::CLOSED)
        {
            ws_->close();
        }
    }

private:
    std::string wsUrl_;
    uint64_t deviceId_;
    easywsclient::WebSocket::pointer ws_;

};

#endif // OPQWEBSOCKET_HPP
