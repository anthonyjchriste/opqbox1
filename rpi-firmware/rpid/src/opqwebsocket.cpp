#include "coresettings.hpp"
#include "datastructures.hpp"
#include "opqpacket.hpp"
#include "opqwebsocket.hpp"
#include "opqjson.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/thread/thread.hpp>
#include <cstdint>
#include <ctime>
#include <stdio.h>
#include <sys/time.h>
#include <stdexcept>
#include <vector>

OpqWebsocket::OpqWebsocket(FrameQueuePointer iq)
{
    opqSettings_ = OpqSettings::Instance();
    wsUrl_ = boost::get<std::string>(opqSettings_->getSetting("ws.url"));
    deviceId_ = boost::get<uint64_t>(opqSettings_->getSetting("device.id"));
    ws_ = easywsclient::WebSocket::from_url(wsUrl_);
    deviceKey_ = boost::get<std::string>(opqSettings_->getSetting("device.key"));
    pingInterval_ = boost::get<int32_t>(opqSettings_->getSetting("device.pinginterval"));


    if(ws_ == NULL) throw std::runtime_error("Websocket not connected");
    //time(&lastPing_);
    //sendPingPacket();
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
                    setValue = boost::lexical_cast<double>(value);
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
            /*
            time(&ts);
            timeDiff = difftime(ts, lastPing_);
            if(timeDiff > pingInterval_)
            {
                sendPingPacket();
                time(&lastPing_);
            }
            */

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
   std::cout << "Got frame!" << "\n";

   OpqParameters parameters = frame->parameters;
   double frequency = (parameters.find("f") == parameters.end()) ? 0.0 : boost::get<double>(parameters["f"]);
   double voltage = (parameters.find("vrms") == parameters.end()) ? 0.0 : boost::get<double>(parameters["vrms"]);

   struct timeval tv;
   gettimeofday(&tv, NULL);
   uint64_t timestamp = (uint64_t) tv.tv_sec * 1000 + (uint64_t) tv.tv_usec / 1000;
   uint32_t packetType = boost::get<int>(parameters["event.type"]);
   std::cout << packetType << "\n";
   std::vector<double> payload;
   for(int i = 0; i < frame->data.size(); i++) {
      payload.push_back(frame->data[i]);
   }

   uint32_t payloadSize = (uint32_t) payload.size();

   char * json;

   jsonify(&json, (uint32_t) 0x00C0FFEE, packetType, deviceId_, deviceKey_, timestamp,
           (uint64_t) 0, (uint32_t) 0, frequency, voltage, (uint32_t) payload.size(), payload);

   std::cout << json << "\n";
   send(std::string(json));
   free(json);
    /*
    uint32_t packetType;
    double eventVal = 0.0;
    OpqPacket packet;

    // Make sure that the fields we need are in the parameters
    if(parameters.find("event.type") == parameters.end()) return;
    packetType = boost::get<int>(parameters["event.type"]);

    switch(packetType)
    {
        case OpqPacketType::EVENT_FREQUENCY:
            if(parameters.find("f") == parameters.end()) return;
            eventVal = boost::get<double>(parameters["f"]);
            break;
        case OpqPacketType::EVENT_VOLTAGE:
            if(parameters.find("vrms") == parameters.end()) return;
            eventVal = boost::get<double>(parameters["vrms"]);
            break;
        case OpqPacketType::MEASUREMENT:
            if(parameters.find("f") == parameters.end()) return;
            if(parameters.find("vrms") == parameters.end()) return;
            eventVal = boost::get<double>(parameters["f"]);
            packet.addPayload(eventVal);
            eventVal = boost::get<double>(parameters["vrms"]);
            packet.addPayload(eventVal);
    }

    // Construct the OPQ packet


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
    */
}

