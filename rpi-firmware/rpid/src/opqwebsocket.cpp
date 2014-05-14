#include "coresettings.hpp"
#include "datastructures.hpp"
#include "opqpacket.hpp"
#include "opqwebsocket.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <cstdint>
#include <ctime>
#include <stdio.h>
#include <sys/time.h>
#include <stdexcept>

OpqWebsocket::OpqWebsocket(FrameQueuePointer iq)
{
    opqSettings_ = OpqSettings::Instance();
    wsUrl_ = boost::get<std::string>(opqSettings_->getSetting("ws.url"));
    deviceId_ = boost::get<uint64_t>(opqSettings_->getSetting("device.id"));
    ws_ = easywsclient::WebSocket::from_url(wsUrl_);
    pingInterval_ = boost::get<int32_t>(opqSettings_->getSetting("device.pinginterval"));

    if(ws_ == NULL) throw std::runtime_error("Websocket not connected");
    time(&lastPing_);
    sendPingPacket();
    iq_ = iq;
}

void OpqWebsocket::callback(std::string message)
{
    OpqPacket recv(message);
    recv.debugInfo();
    std::string p((const char *)recv.payload.data());

    vector<std::string> tokens;
    boost::split(tokens, p, boost::is_any_of(":"));

    std::string setting = tokens[0];
    std::string type =  tokens[1];
    std::string value = tokens[2];

    std::cout << setting << " " << type << " " << value << std::endl << std::flush;
    switch(recv.header.type)
    {
        case OpqPacketType::SETTING: {
            OpqSetting setValue;
            switch (type.at(0))
            {
                case 'U':
                    setValue = boost::lexical_cast<uint64_t>(value);
                    break;
                case 'F':
                    setValue = boost::lexical_cast<float>(value);
                    break;
                case 'I':
                    setValue = boost::lexical_cast<int>(value);
                    break;
                case 'S':
                    setValue = value;
                    break;
                case 'B':
                    if(value == "TRUE")
                        setValue = true;
                    else
                        setValue = false;
                    break;
                default:
                    throw boost::bad_lexical_cast();
            }

            opqSettings_->setSetting(setting, setValue);
            opqSettings_->saveToFile("settings.set");
            break;
        }

     default:
        break;
    }
}

void OpqWebsocket::run()
{
    time_t ts;
    double timeDiff;

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
                boost::function<void (std::string)> f;
                f = boost::bind(&OpqWebsocket::callback, this, _1);
                ws_->poll(10);
                ws_->dispatch(f);
            }

            // Check if we need to send a ping
            time(&ts);
            timeDiff = difftime(ts, lastPing_);
            if(timeDiff > pingInterval_)
            {
                sendPingPacket();
                time(&lastPing_);
            }

            // Check if we've been interrupted
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
        for(int i = 0; i < frame->data.size(); i++)
        {
            packet.addPayload(frame->data[i]);
        }
    }

    packet.computeChecksum();

    // To the cloud!
    send(packet);
}

