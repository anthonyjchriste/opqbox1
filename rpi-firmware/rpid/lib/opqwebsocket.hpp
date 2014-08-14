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
    void init();
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
        delete ws_;
    }

private:
    std::string wsUrl_;
    uint64_t deviceId_;
    std::string deviceKey_;
    easywsclient::WebSocket::pointer ws_;
    void handleFrame(OpqFrame *frame);
    void constructAndSend(OpqFrame *frame);
    FrameQueuePointer iq_;
    time_t lastPing_;
    time_t lastEvent_;
    uint32_t pingInterval_; // In seconds
    uint32_t throttle_; // In seconds
    OpqSettings *opqSettings_;
    void callback(std::string);
};

#endif // OPQWEBSOCKET_HPP
