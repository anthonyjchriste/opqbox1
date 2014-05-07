#include "coresettings.hpp"
#include "opqwebsocket.hpp"
#include <assert.h>
#include <stdio.h>
#include <boost/thread.hpp>
#include <functional>

OpqWebsocket::OpqWebsocket()
{
    OpqSettings* opqSettings = OpqSettings::Instance();
    wsUrl_ = boost::get<std::string>(opqSettings->getSetting("ws.url"));
    ws_ = easywsclient::WebSocket::from_url(wsUrl_);
}

void OpqWebsocket::handleMessage(std::string &message)
{
    printf("received %s\n", message.c_str());
}

void OpqWebsocket::listen()
{
    while(ws_->getReadyState() != easywsclient::WebSocket::CLOSED) {
        // Check for messages
        while(!messages.empty()) {
            ws_->send(messages.front());
            messages.pop();
        }

        ws_->poll();
        //ws_->dispatch(handleMessage);
        ws_->dispatch(*this);

        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

    }
}

void OpqWebsocket::operator ()(std::string message) {
    handleMessage(message);
}
