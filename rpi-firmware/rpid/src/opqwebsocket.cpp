#include "coresettings.hpp"
#include "datastructures.hpp"
#include "opqpacket.hpp"
#include "opqwebsocket.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <cstdint>
#include <stdio.h>

OpqWebsocket::OpqWebsocket()
{
    OpqSettings* opqSettings = OpqSettings::Instance();
    wsUrl_ = boost::get<std::string>(opqSettings->getSetting("ws.url"));
    deviceId_ = boost::get<uint64_t>(opqSettings->getSetting("device.id"));
    ws_ = easywsclient::WebSocket::from_url(wsUrl_);
}

auto cb = [](std::string message)
{
    printf("%s\n", message.c_str());
};

void OpqWebsocket::send(std::string message)
{
    if(ws_ != NULL && ws_->getReadyState() == easywsclient::WebSocket::OPEN)
    {
        ws_->send(message);
    }
}

void OpqWebsocket::send(OpqPacket packet)
{
    send(packet.encodeOpqPacket());
}

void OpqWebsocket::consumeQueue()
{
    struct OpqFrame frame;
    while(!frames.empty())
    {
        OpqPacket packet;
        frame = frames.front();
        frames.pop();

        //packet.header.type =
        packet.header.sequenceNumber = 0;
        packet.header.deviceId = deviceId_;
        packet.header.timestamp = (uint64_t) frame.timeSec * 1000 + (uint64_t) frame.timeUsec / 1000;
        packet.header.bitfield = 0;
        // payload stuff
        packet.computeChecksum();
        send(packet);
    }
}

/*
void OpqWebsocket::listen()
{
    while(ws_->getReadyState() != easywsclient::WebSocket::CLOSED) {
        // Check for messages
        while(!messages.empty()) {
            ws_->send(messages.front());
            messages.pop();
        }

        ws_->poll();
        ws_->dispatch(cb);

        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

    }
}
*/
