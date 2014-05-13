#ifndef OPQWEBSOCKET_HPP
#define OPQWEBSOCKET_HPP

#include "datastructures.hpp"
#include "easywsclient.hpp"
#include "opqpacket.hpp"

#include <cstdint>
#include <ctime>
#include <string>
#include <queue>

class OpqWebsocket
{
public:
    OpqWebsocket(FrameQueuePointer iq);
    void listen();
    void send(std::string message);
    void send(OpqPacket packet);
    void sendPingPacket();
    void run();
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
    void handleFrame(OpqFrame *frame);
    FrameQueuePointer iq_;
    time_t lastPing_;
    uint32_t pingInterval_; // In seconds
};

#endif // OPQWEBSOCKET_HPP
