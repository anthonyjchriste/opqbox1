#include "coresettings.hpp"
#include "opqwebsocket.hpp"
#include <assert.h>
#include <stdio.h>
#include <boost/thread.hpp>
#include <functional>
#include <iostream>

OpqWebsocket::OpqWebsocket()
{
    OpqSettings* opqSettings = OpqSettings::Instance();
    wsUrl_ = boost::get<std::string>(opqSettings->getSetting("ws.url"));
    ws_ = easywsclient::WebSocket::from_url(wsUrl_);
}

auto cb = [](std::string message)
    {
        printf("%s\n", message.c_str());
    };

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

