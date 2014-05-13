#include "coresettings.hpp"
#include "datastructures.hpp"
#include "opqpacket.hpp"
#include "opqwebsocket.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <cstdint>
#include <stdio.h>
#include <sys/time.h>
#include <stdexcept>

OpqWebsocket::OpqWebsocket(FrameQueuePointer iq)
{
    OpqSettings* opqSettings = OpqSettings::Instance();
    wsUrl_ = boost::get<std::string>(opqSettings->getSetting("ws.url"));
    deviceId_ = boost::get<uint64_t>(opqSettings->getSetting("device.id"));
    ws_ = easywsclient::WebSocket::from_url(wsUrl_);
    if(ws_ == NULL) throw std::runtime_error("Websocket not connected");
    iq_ = iq;
}



void OpqWebsocket::run()
{
    auto cb = [](std::string message)
    {
        printf("%s\n", message.c_str());
    };

    try
    {
        while(true)
        {
            // Check device queue
            bool ok;
            OpqFrame* next = iq_->pop_timeout(10, ok);
            if(ok) {
                handleFrame(next);
                delete next;
            }

            // Check for messages from cloud
            if(ws_ != NULL)
            {
                ws_->poll(10);
                ws_->dispatch(cb);
            }
            boost::this_thread::interruption_point();
        }
    }
    catch(boost::thread_interrupted &e)
    {
        return;
    }
}

void OpqWebsocket::send(std::string message)
{
    if(ws_ != NULL && ws_->getReadyState() == easywsclient::WebSocket::OPEN)
    {
        ws_->send(message);
    }
}

void OpqWebsocket::sendPingPacket()
{
    OpqPacket packet;
    struct timeval tv;
    gettimeofday(&tv, NULL);

    packet.header.type = OpqPacketType::PING;
    packet.header.sequenceNumber = 0;
    packet.header.deviceId = deviceId_;
    packet.header.timestamp = (uint64_t) tv.tv_sec * 1000 + (uint64_t) tv.tv_usec / 1000;
    packet.header.bitfield = 0;
    packet.computeChecksum();
    send(packet);
}

void OpqWebsocket::send(OpqPacket packet)
{
    send(packet.encodeOpqPacket());
}

void OpqWebsocket::handleFrame(OpqFrame *frame)
{
    OpqParameters parameters = frame->parameters;
    uint32_t packetType;
    double eventVal = 0.0;


    // Make sure that the fields we need are in the parameters
    if(parameters.find("opqPacketType") == parameters.end()) return;
    packetType = boost::get<uint8_t>(parameters["opqPacketType"]);

    switch(packetType)
    {
        case OpqPacketType::EVENT_FREQUENCY:
            if(parameters.find("f") == parameters.end()) return;
            eventVal = boost::get<double>(parameters["frequency"]);
            break;
        case OpqPacketType::EVENT_VOLTAGE:
            if(parameters.find("vrms") == parameters.end()) return;
            eventVal = boost::get<double>(parameters["voltage"]);
            break;
    }

    // Construct the OPQ packet
    OpqPacket packet;

    packet.header.type = packetType;
    packet.header.sequenceNumber = 0;
    packet.header.deviceId = deviceId_;
    packet.header.timestamp = (uint64_t) frame->timeSec * 1000 + (uint64_t) frame->timeUsec / 1000;
    packet.header.bitfield = 0;

    // Handle the payload
    if(packetType == OpqPacketType::EVENT_FREQUENCY || packetType == OpqPacketType::EVENT_VOLTAGE)
    {
        packet.addPayload(eventVal);
        packet.addPayload((uint64_t) 0);
    }

    packet.computeChecksum();

    // To the cloud!
    send(packet);

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
